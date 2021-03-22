#ifndef MPW_HAMSTER_EXAMPLES_RACEHAMSTER_H
#define MPW_HAMSTER_EXAMPLES_RACEHAMSTER_H

#include "Hamster.h"

class RaceHamster {
public:
    RaceHamster(const mpw::Location& location, const mpw::Direction direction, const int grainCount) :
            myHamster(location,direction,grainCount) {};
    hamster::Hamster& getHamster() { return myHamster; };
    void pickAndCount() {
        myHamster.pickGrain();
        grainCollected++;
    }
    int getNumberOfCollectedGrains() const { return grainCollected; };
    void beginRightTurn() {
        myHamster.turnLeft();
        leftTurnsLeft = 2;
    }
    void performRemainingRightTurn() {
        myHamster.turnLeft();
        leftTurnsLeft--;
    }
    bool hasRemainingLeftTurnsForRightTurn() const {
        return leftTurnsLeft > 0;
    }
private:
    hamster::Hamster myHamster;
    int grainCollected = 0;
    int leftTurnsLeft = 0;
};

extern const int HAMSTER_COUNT = 4;

#endif //MPW_HAMSTER_EXAMPLES_RACEHAMSTER_H
