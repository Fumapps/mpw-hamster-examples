#include "racehamster.h"
#include "HamsterRaceGame.h"
#include <vector>
#include <SimpleHamsterGame.h>

void doHamsterObjectRace();
bool hamsterWon(std::vector<RaceHamster>& raceHamsters);
bool hasEnoughGrains(const RaceHamster& raceHamster);
void executeSingleCommand(RaceHamster& raceHamster);

int main()
{
    HamsterRaceGame game;
    game.doRun();
    return 0;
}

/**
 * Initialize 4 race hamsters and store their data in an array.
 * Each one sitting at its start position and looking towards east.
 * Then the main loop iterates until one hamster has won the
 * game. In each iteration each hamster is asked to perform
 * exactly one step.
 */
void doHamsterObjectRace()
{
    // std::vector<RaceHamster> raceHamsters = std::vector<RaceHamster>();
    // raceHamsters.emplace_back(Location(1, 7), Direction::EAST, 0);
    // raceHamsters.emplace_back(Location(3, 5), Direction::EAST, 0);
    // raceHamsters.emplace_back(Location(5, 3), Direction::EAST, 0);
    // raceHamsters.emplace_back(Location(7, 1), Direction::EAST, 0);
//
    // while (!hamsterWon(raceHamsters))
    // {
    //     for (RaceHamster& hamster : raceHamsters)
    //     {
    //         executeSingleCommand(hamster);
    //     }
    // }
}

/** Checks if one of the hamsters in the array has won the game.
 */
bool hamsterWon(std::vector<RaceHamster>& raceHamsters)
{
    for (const RaceHamster& hamster : raceHamsters)
    {
        if (hasEnoughGrains(hamster))
        {
            return true;
        }
    }
    return false;
}

/** returns true if the passed hamster has collected
 * enough grains to win the game
 */
bool hasEnoughGrains(const RaceHamster& raceHamster)
{
    return raceHamster.getNumberOfCollectedGrains() == 2;
}

/**
* Perform a single action for the given race hamster.
* Actions are choosen with the following priorities:
* First remaining turns to implement a right turn are executed.
* Then available grains are picked up, and then moves are executed
* as long as frontIsFree. Finally, in case of a blocked tile, a right
* turn is initiated.
*/
void executeSingleCommand(RaceHamster& raceHamster)
{
    if (raceHamster.hasRemainingLeftTurnsForRightTurn())
    {
        raceHamster.performRemainingRightTurn();
    }
    else if (raceHamster.getHamster().grainAvailable())
    {
        raceHamster.pickAndCount();
    }
    else if (raceHamster.getHamster().frontIsClear())
    {
        raceHamster.getHamster().move();
    }
    else
    {
        raceHamster.beginRightTurn();
    }
}

