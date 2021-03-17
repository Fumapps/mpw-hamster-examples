#include "SimpleHamsterGame.h"

using namespace hamster;

class FirstHamsterExample : public hamstersimulator::SimpleHamsterGame {
protected:
    void run() override;
};

void FirstHamsterExample::run() {
    // displayInNewGameWindow();
    paule.move();
    paule.move();
    paule.pickGrain();
    paule.turnLeft();
    paule.turnLeft();
    paule.move();
    paule.move();
    paule.putGrain();
    paule.turnLeft();
    paule.turnLeft();
    paule.move();
}

int main() {
    hamstersimulator::SimpleHamsterGame::createInstance<FirstHamsterExample>();
    return 0;
}

