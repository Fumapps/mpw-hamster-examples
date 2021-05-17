#include "rss-hamster/rss-hamster.h"

int main() {
    init("ter/looping.ter");
    int count = 0;
    HamsterSpec willi = addHamster(0,0, EAST,0);
    move(willi);
    turnLeft(willi);
    turnLeft(willi);
    turnLeft(willi);
    while(frontIsClear()) {
        move();
        count++;
        writef("I'm walking: %d", count);
    }
    deinit();
    return 0;
}
