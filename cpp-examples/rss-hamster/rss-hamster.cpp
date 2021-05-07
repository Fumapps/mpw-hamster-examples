#include "rss-hamster.h"
#include <thread>
#include <chrono>
#include "MpwSemaphore.h"

using namespace mpw;
using namespace hamster;
using namespace hamstersimulator;

SimpleHamsterGameDummy* runningGame = nullptr;
std::thread gui_thread;
framework::Semaphore gameRunnerLock;
framework::Semaphore guiInitializerLock;

void SimpleHamsterGameDummy::run() {
	runningGame = this;
	loadTerritoryFromResourceFile("ter/looping.ter");
	game->startGame();
	guiInitializerLock.release();
	gameRunnerLock.acquire();
	gameRunnerLock.acquire();
};

void main_gui() {
	SimpleHamsterGameDummy::createInstance<SimpleHamsterGameDummy>();
}

void init() {
	std::thread gui(main_gui);
	gui_thread = std::move(gui);
	guiInitializerLock.acquire();
	guiInitializerLock.acquire();
}

void move() {
	runningGame->getHamster().move();
}

void turnLeft() {
	runningGame->getHamster().turnLeft();
}

void deinit() {
	gameRunnerLock.release();
	gui_thread.join();
	runningGame = nullptr;
}