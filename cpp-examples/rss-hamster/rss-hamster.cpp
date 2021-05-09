#include "rss-hamster.h"
#include "MpwSemaphore.h"
#include <thread>
#include <Mode.h>

extern int main(void);

void execCommand(const std::function<void(Hamster&)>&);

using namespace mpw;
using namespace hamster;
using namespace hamstersimulator;

SimpleHamsterGameDummy* runningGame = nullptr;
framework::Semaphore gameRunnerLock;
framework::Semaphore guiInitializerLock;

void SimpleHamsterGameDummy::run() {
	runningGame = this;
	loadTerritoryFromResourceFile("ter/looping.ter");
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
            command(this->getHamster());
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

void init() {
    static volatile bool firstRun = true;
    if (firstRun) {
        firstRun = false;
        SimpleHamsterGameDummy::createInstance<SimpleHamsterGameDummy>();
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

bool frontIsClear() {
    return runningGame->getHamster().frontIsClear();
}

bool grainAvailable() {
    return runningGame->getHamster().grainAvailable();
}

bool mouthIsEmpty() {
    return runningGame->getHamster().mouthEmpty();
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
