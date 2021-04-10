package de.unistuttgart.iste.sqa.oo.hamstersimulator.race;

import de.unistuttgart.hamster.facade.Territory;
import de.unistuttgart.hamster.main.SimpleHamsterGame;
import de.unistuttgart.iste.sqa.mpw.framework.datatypes.Direction;
import de.unistuttgart.iste.sqa.mpw.framework.datatypes.Location;

import java.util.ArrayList;
import java.util.List;

/**
 * This class represents a HamsterRaceGame. It comes with a specific territory
 * and owns a list of racers.
 */
public class HamsterRaceGame extends SimpleHamsterGame {

    private final List<RaceHamster> raceHamsters;

    public HamsterRaceGame() {
        loadTerritoryFromResourceFile("raceterritories/race2.ter");
        game.startGamePaused();
        displayInNewGameWindow();
        raceHamsters = new ArrayList<>();
    }

    @Override
    protected void run() {
        initRace();
        doHamsterObjectRace();
    }

    /**
     * Initialize 4 race hamsters and store their data in a list.
     * Each one sitting at its start position and looking towards east.
     */
    private void initRace() {
        final Territory territory = game.getTerritory();

        raceHamsters.add(new RaceHamster(territory, Location.from(1, 7), Direction.EAST));
        raceHamsters.add(new RaceHamster(territory, Location.from(3, 5), Direction.EAST));
        raceHamsters.add(new RaceHamster(territory, Location.from(5, 3), Direction.EAST));
        raceHamsters.add(new RaceHamster(territory, Location.from(7, 1), Direction.EAST));
    }

    /**
     * The main loop iterates until one hamster has won the
     * game. In each iteration each hamster is asked to perform
     * exactly one step.
     */
    private void doHamsterObjectRace() {
        while (!hamsterWon()) {
            for (RaceHamster hamster : raceHamsters) {
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
    void executeSingleCommand(RaceHamster raceHamster) {
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
    boolean hasEnoughGrains(RaceHamster raceHamster) {
        return raceHamster.getNumberOfCollectedGrains() == 2;
    }

    /**
     * Checks if one of the hamsters in the array has won the game.
     */
    boolean hamsterWon() {
        for (RaceHamster hamster : raceHamsters) {
            if (hasEnoughGrains(hamster)) {
                return true;
            }
        }
        return false;
    }
}
