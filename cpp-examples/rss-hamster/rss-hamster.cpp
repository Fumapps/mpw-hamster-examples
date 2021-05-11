#include "rss-hamster.h"
#include "MpwSemaphore.h"
#include <thread>
#include <Mode.h>

extern int main(void);

void execCommand(const std::function<void(Hamster&)>&);

using namespace mpw;
using namespace hamster;
using namespace hamstersimulator;

SimpleHamsterGameInC* runningGame = nullptr;
framework::Semaphore gameRunnerLock;
framework::Semaphore guiInitializerLock;

void SimpleHamsterGameInC::run() {
	runningGame = this;
	loadTerritoryFromResourceFile(this->territoryFilename);
	game->startGame();
	guiInitializerLock.release();

	std::thread mainThread([](){
	    try {
            ::main();
        } catch (std::exception ex) {};
	});

    while (const std::function<void(Hamster&)>& command = commandQueue.front()) {
        commandQueue.pop();
        try {
            command(this->getDefaultHamster());
            resultQueue.push(std::optional<std::exception>());
        } catch (std::exception& e) {
            resultQueue.push(std::make_optional(e));
            this->game->confirmAlert(e);
            this->game->stopGame();
            break;
        }
    }
    resultQueue.push(std::optional<std::exception>());
    mainThread.join();
};

void init(void) {
    init("ter/looping.ter");
}

void init(const char* territoryFilename) {
    static volatile bool firstRun = true;
    if (firstRun) {
        firstRun = false;
        std::string filename(territoryFilename);
        SimpleHamsterGameInC::createInstance(filename);
        exit(0);
    } else {
        guiInitializerLock.acquire();
        guiInitializerLock.acquire();
    }
}

void turnLeft() {
    execCommand(&hamster::Hamster::turnLeft);
}

void move() {
    execCommand(&hamster::Hamster::move);
}

void pickGrain() {
    execCommand(&hamster::Hamster::pickGrain);
}

void putGrain() {
    execCommand(&hamster::Hamster::putGrain);
}

void write(const char *message) {
    runningGame->getDefaultHamster().write(message);
}

void writef(const char *message_template, ...)
{
    char buffer[1000];
    va_list args;
    va_start(args, message_template);
    vsnprintf(buffer, 1000, message_template, args);
    write(buffer);
    va_end(args);
}

bool frontIsClear() {
    return runningGame->getDefaultHamster().frontIsClear();
}

bool grainAvailable() {
    return runningGame->getDefaultHamster().grainAvailable();
}

bool mouthEmpty() {
    return runningGame->getDefaultHamster().mouthEmpty();
}

void deinit() {
    runningGame->sendCommand(nullptr);
	gameRunnerLock.release();
	runningGame = nullptr;
}

void execCommand(const std::function<void(Hamster&)>& f) {
    auto result = runningGame->sendCommand(f);
    if (result.has_value()) {
        throw result.value();
    }
}
