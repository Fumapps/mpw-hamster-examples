#include "rss-hamster.h"
#include "MpwSemaphore.h"
#include <thread>
#include <Mode.h>

extern int main(void);

void execCommand(const std::function<void(Hamster&)>&);
void execCommand(Hamster& hamster, const std::function<void(Hamster&)>&);

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

    bool terminate = false;
    do {
        const HamsterAndCommand& command = commandQueue.front();
        commandQueue.pop();
        if (command.function != nullptr) {
            try {
                command.function(command.target);
                resultQueue.push(std::optional<std::exception>());
            } catch (std::exception &e) {
                resultQueue.push(std::make_optional(e));
                this->game->confirmAlert(e);
                this->game->stopGame();
                break;
            }
        } else {
            terminate = true;
        }
    } while (!terminate);
    resultQueue.push(std::optional<std::exception>());
    mainThread.join();
}

Direction getDirection(int direction) {
    switch(direction) {
        case NORTH: return Direction::NORTH;
        case SOUTH: return Direction::SOUTH;
        case EAST: return Direction::EAST;
        case WEST: return Direction::WEST;
        default: throw std::exception();
    }
}

HamsterSpec SimpleHamsterGameInC::addHamster(int row, int column, int direction, int grainCount) {
    Location newLocation(column,row);
    Direction newDirection = getDirection(direction);
    return HamsterSpec(additionalHamsters.emplace_back(runningGame->game->getTerritory(), newLocation, newDirection, grainCount));
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

void turnLeft(HamsterSpec hamster) {
    execCommand(hamster.hamster,&hamster::Hamster::turnLeft);
}

void move() {
    execCommand(&hamster::Hamster::move);
}

void move(HamsterSpec hamster) {
    execCommand(hamster.hamster, &hamster::Hamster::move);
}

void pickGrain() {
    execCommand(&hamster::Hamster::pickGrain);
}

void pickGrain(HamsterSpec hamster) {
    execCommand(hamster.hamster,&hamster::Hamster::pickGrain);
}

void putGrain() {
    execCommand(&hamster::Hamster::putGrain);
}

void putGrain(HamsterSpec hamster) {
    execCommand(hamster.hamster,&hamster::Hamster::putGrain);
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
    runningGame->sendCommand(runningGame->getDefaultHamster(), nullptr);
	gameRunnerLock.release();
	runningGame = nullptr;
}

void execCommand(const std::function<void(Hamster&)>& f) {
    execCommand(runningGame->getDefaultHamster(), f);
}

void execCommand(Hamster& target, const std::function<void(Hamster&)>& f) {
    auto result = runningGame->sendCommand(target, f);
    if (result.has_value()) {
        throw result.value();
    }
}

HamsterSpec addHamster(int row, int column, int direction, int grainCount) {
    return runningGame->addHamster(row, column, direction, grainCount);
}

HamsterSpec::HamsterSpec(Hamster &hamster) : hamster(hamster) {}

HamsterAndCommand::HamsterAndCommand(Hamster &target, std::function<void(Hamster &)> function) : target(target), function(function) {}
