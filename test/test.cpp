#include <gtest/gtest.h>
#include <game.h>
#include <referee.h>
#include <choice.h>
#include <optional>
#include <player.h>

TEST(Choice, Correctness) {

   Referee<Choice> referee;

   // Scissors won
   EXPECT_EQ(Choice::Scissors, referee.winner(Choice::Scissors, Choice::Paper));
   EXPECT_EQ(Choice::Scissors, referee.winner(Choice::Paper, Choice::Scissors));

   // Paper won
   EXPECT_EQ(Choice::Paper, referee.winner(Choice::Rock, Choice::Paper));
   EXPECT_EQ(Choice::Paper, referee.winner(Choice::Paper, Choice::Rock));

   // Rock won
   EXPECT_EQ(Choice::Rock, referee.winner(Choice::Rock, Choice::Scissors));
   EXPECT_EQ(Choice::Rock, referee.winner(Choice::Scissors, Choice::Rock));

   // Draw
   EXPECT_EQ(std::nullopt, referee.winner(Choice::Rock, Choice::Rock));
   EXPECT_EQ(std::nullopt, referee.winner(Choice::Rock, Choice::Rock));
   EXPECT_EQ(std::nullopt, referee.winner(Choice::Scissors, Choice::Scissors));
   EXPECT_EQ(std::nullopt, referee.winner(Choice::Paper, Choice::Paper));
}

TEST(Construct, GameBuilder) {
    const int rounds = 10;
    auto game = GameBuilder<Player<Computer>, Player<Computer>, Choice, Writer<Dummy>>()
        .computer(Player<Computer>())
        .human(Player<Computer>())
        .rounds(rounds)
        .build();

    game.run();
    EXPECT_EQ(game.winner_history().size(), rounds);
    EXPECT_EQ(game.play_history().size(), rounds);
}

TEST(Construct, PlayerHuman) {
    auto human = Player<Human>();
}

TEST(Construct, PlayerComputer) {
    auto com = Player<Computer>();
    auto c = com.play();
}

TEST(Construct, WriterStdout) {
    auto game = GameBuilder<Player<Computer>, Player<Computer>>()
        .computer(Player<Computer>("Computer 1"))
        .human(Player<Computer>("Computer 2"))
        .rounds(1)
        .build();
    game.run();
}

