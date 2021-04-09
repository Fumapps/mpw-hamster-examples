#include "HamsterRaceGame.h"

using namespace mpw;
using namespace hamster;
using namespace hamstersimulator;

void HamsterRaceGame::run() {
    initRace();
    doHamsterObjectRace();
}

void HamsterRaceGame::initRace() {
    loadTerritoryFromResourceFile("ter/race2.ter");
    game->startGamePaused();
}

/**
 * Initialize 4 race hamsters and store their data in an array.
 * Each one sitting at its start position and looking towards east.
 * Then the main loop iterates until one hamster has won the
 * game. In each iteration each hamster is asked to perform
 * exactly one step.
 */
void HamsterRaceGame::doHamsterObjectRace() {
    Territory& territory = *game->getTerritory();

    std::vector<RaceHamster> raceHamsters = std::vector<RaceHamster>();
    raceHamsters.emplace_back(territory, Location(1, 7), Direction::EAST, 0);
    raceHamsters.emplace_back(territory, Location(3, 5), Direction::EAST, 0);
    raceHamsters.emplace_back(territory, Location(5, 3), Direction::EAST, 0);
    raceHamsters.emplace_back(territory, Location(7, 1), Direction::EAST, 0);

    while (!hamsterWon(raceHamsters)) {
        for (RaceHamster& hamster : raceHamsters) {
            executeSingleCommand(hamster);
        }
    }
}

/**
* Perform a single action for the given race hamster.
* Actions are choosen with the following priorities:
* First remaining turns to implement a right turn are executed.
* Then available grains are picked up, and then moves are executed
* as long as frontIsFree. Finally, in case of a blocked tile, a right
* turn is initiated.
*/
void HamsterRaceGame::executeSingleCommand(RaceHamster& raceHamster) {
    if (raceHamster.hasRemainingLeftTurnsForRightTurn()) {
        raceHamster.performRemainingRightTurn();
    } else if (raceHamster.grainAvailable()) {
        raceHamster.pickAndCount();
    } else if (raceHamster.frontIsClear()) {
        raceHamster.move();
    } else {
        raceHamster.beginRightTurn();
    }
}

/**
 * returns true if the passed hamster has collected
 * enough grains to win the game
 */
bool HamsterRaceGame::hasEnoughGrains(const RaceHamster& raceHamster) {
    return raceHamster.getNumberOfCollectedGrains() == 2;
}

/**
 * Checks if one of the hamsters in the array has won the game.
 */
bool HamsterRaceGame::hamsterWon(std::vector<RaceHamster>& raceHamsters) {
    for (const RaceHamster& hamster : raceHamsters) {
        if (hasEnoughGrains(hamster)) {
            return true;
        }
    }
    return false;
}

