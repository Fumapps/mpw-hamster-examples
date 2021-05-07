#pragma once
#include "SimpleHamsterGame.h"

using namespace mpw;
using namespace hamster;
using namespace hamstersimulator;

class SimpleHamsterGameDummy : public SimpleHamsterGame {
public:
	Hamster& getHamster() const {
		return this->paule;
	}
	void run() override;
};

extern SimpleHamsterGameDummy* runningGame;

void init(void);
void move(void);
void turnLeft(void);
void deinit(void);