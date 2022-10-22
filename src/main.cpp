#include <util.h>
#include <choice.h>
#include <player.h>
#include <game.h>
#include <referee.h>

int main() {
    auto game = GameBuilder<Player<Computer>, Player<Human>>()
        .computer(Player<Computer>())
        .human(Player<Human>())
        .rounds(10)
        .build();

    game.run();

	return 0;
}
