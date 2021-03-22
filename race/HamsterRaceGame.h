#ifndef MPW_HAMSTER_EXAMPLES_HAMSTERRACEGAME_H
#define MPW_HAMSTER_EXAMPLES_HAMSTERRACEGAME_H

#include "SimpleHamsterGame.h"

class HamsterRaceGame : public hamstersimulator::SimpleHamsterGame {
protected:
    void run() override;

    void initRace();
    void doRace();
};

#endif //MPW_HAMSTER_EXAMPLES_HAMSTERRACEGAME_H
