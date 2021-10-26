#include "game.h"
#include "utils.h"
#include <stdio.h>

int main() {
    printf("creating game\n");
    Game game = Game(800, 600, "AwesomeGame");
    printf("running game\n");
    game.Run();

    return 0;
}
