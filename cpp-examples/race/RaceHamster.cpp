#include "RaceHamster.h"

extern const int HAMSTER_COUNT = 4;

RaceHamster::RaceHamster(hamster::Territory& territory, const mpw::Location& location,
                         const mpw::Direction direction, const int grainCount) :
        Hamster(territory.shared_from_this(), location, direction, grainCount) {}

void RaceHamster::pickAndCount() {
    Hamster::pickGrain();
    grainCollected++;
}

int RaceHamster::getNumberOfCollectedGrains() const { return grainCollected; }

void RaceHamster::beginRightTurn() {
    Hamster::turnLeft();
    leftTurnsLeft = 2;
}

void RaceHamster::performRemainingRightTurn() {
    Hamster::turnLeft();
    leftTurnsLeft--;
}

bool RaceHamster::hasRemainingLeftTurnsForRightTurn() const {
    return leftTurnsLeft > 0;
}
