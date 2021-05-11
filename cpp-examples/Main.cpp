#include "rss-hamster/rss-hamster.h"

int main() {
    init();
    int count = 0;
    while(frontIsClear()) {
        move();
        count++;
        writef("I'm walking: %d", count);
    }
    deinit();
    return 0;
}
