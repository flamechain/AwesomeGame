#include "game.h"
#include "utils.h"

#include <stdio.h>

int main() {
    Game game = Game(800, 600, "AwesomeGame");
    game.Run();

    return 0;
}
