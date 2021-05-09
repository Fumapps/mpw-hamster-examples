#pragma once

#include <Mode.h>
#include "SimpleHamsterGame.h"
#include "blocking_queue.h"

using namespace mpw;
using namespace hamster;
using namespace hamstersimulator;

class SimpleHamsterGameDummy : public SimpleHamsterGame {
private:
    blocking_queue<std::function<void(Hamster&)>> commandQueue;
    blocking_queue<std::optional<std::exception>> resultQueue;
public:
    SimpleHamsterGameDummy() : commandQueue(1), resultQueue(1){};
	Hamster& getHamster() const {
		return this->paule;
	}
	void run() override;
	std::optional<std::exception> sendCommand(std::function<void(Hamster&)> command) {
        commandQueue.push(command);
        auto result = resultQueue.front();
        resultQueue.pop();
        return result;
	}
};

extern SimpleHamsterGameDummy* runningGame;

void init(void);
void move(void);
void turnLeft(void);
void pickGrain(void);
void putGrain(void);
void deinit(void);
bool frontIsClear(void);
bool grainAvailable(void);
bool mouthIsEmpty(void);