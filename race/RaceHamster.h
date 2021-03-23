#ifndef MPW_HAMSTER_EXAMPLES_RACEHAMSTER_H
#define MPW_HAMSTER_EXAMPLES_RACEHAMSTER_H

#include "Hamster.h"
#include "Territory.h"

class RaceHamster : public hamster::Hamster {
public:
    RaceHamster(hamster::Territory& territory, const mpw::Location& location,
                mpw::Direction direction, int grainCount);

    void pickAndCount();

    int getNumberOfCollectedGrains() const;;

    void beginRightTurn();

    void performRemainingRightTurn();

    bool hasRemainingLeftTurnsForRightTurn() const;

private:

    int grainCollected = 0;
    int leftTurnsLeft = 0;
};

extern const int HAMSTER_COUNT;

#endif //MPW_HAMSTER_EXAMPLES_RACEHAMSTER_H
