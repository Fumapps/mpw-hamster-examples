package de.unistuttgart.iste.sqa.oo.hamstersimulator.race;

import de.unistuttgart.hamster.facade.Hamster;
import de.unistuttgart.hamster.facade.Territory;
import de.unistuttgart.iste.sqa.mpw.framework.datatypes.Direction;
import de.unistuttgart.iste.sqa.mpw.framework.datatypes.Location;

public class RaceHamster extends Hamster {
    private int grainCollected = 0;
    private int leftTurnsLeft = 0;

    public RaceHamster(Territory territory,
                       Location location,
                       Direction direction) {
        super(territory, location, direction, 0);
    }

    public void pickAndCount() {
        super.pickGrain();
        grainCollected++;
    }

    public int getNumberOfCollectedGrains() {
        return grainCollected;
    }

    public void beginRightTurn() {
        super.turnLeft();
        leftTurnsLeft = 2;
    }

    public void performRemainingRightTurn() {
        super.turnLeft();
        leftTurnsLeft--;
    }

    public boolean hasRemainingLeftTurnsForRightTurn() {
        return leftTurnsLeft > 0;
    }
}
