#ifndef MPW_HAMSTER_EXAMPLES_HAMSTERRACEGAME_H
#define MPW_HAMSTER_EXAMPLES_HAMSTERRACEGAME_H

#include "SimpleHamsterGame.h"
#include "RaceHamster.h"

/**
 * This class represents a HamsterRaceGame. It comes with a specific territory
 * and owns a list of racers.
 */
class HamsterRaceGame : public hamstersimulator::SimpleHamsterGame {
private:
    std::vector<RaceHamster> raceHamsters;

protected:
    void run() override;

    void initRace();
    void doHamsterObjectRace();
    static void executeSingleCommand(RaceHamster& raceHamster);
    bool hamsterWon();
    static bool hasEnoughGrains(const RaceHamster& raceHamster);
};

#endif //MPW_HAMSTER_EXAMPLES_HAMSTERRACEGAME_H
