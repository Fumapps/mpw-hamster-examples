#ifndef MPW_HAMSTER_EXAMPLES_HAMSTERRACEGAME_H
#define MPW_HAMSTER_EXAMPLES_HAMSTERRACEGAME_H

#include "SimpleHamsterGame.h"
#include "RaceHamster.h"

class HamsterRaceGame : public hamstersimulator::SimpleHamsterGame {
protected:
    void run() override;

    void initRace();
    void doHamsterObjectRace();
    static void executeSingleCommand(RaceHamster& raceHamster);
    static bool hamsterWon(std::vector<RaceHamster>& raceHamsters);
    static bool hasEnoughGrains(const RaceHamster& raceHamster);
};

#endif //MPW_HAMSTER_EXAMPLES_HAMSTERRACEGAME_H
