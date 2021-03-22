#include "HamsterRaceGame.h"

using namespace hamster;
using namespace hamstersimulator;

void HamsterRaceGame::run() {
    initRace();
    doRace();
}

void HamsterRaceGame::initRace() {
    loadTerritoryFromResourceFile("/ter/race2.ter");
}

void HamsterRaceGame::doRace() {

}
