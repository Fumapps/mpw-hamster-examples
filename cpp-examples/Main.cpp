#include "rss-hamster/rss-hamster.h"

int main() {
    init();
    //turnLeft();
    while(frontIsClear()) {
        move();
    }
    deinit();
    return 0;
}
