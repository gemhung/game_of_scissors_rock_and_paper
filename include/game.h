#ifndef GAME_HEADER
#define GAME_HEADER

#include <time.h>
#include <iostream>
#include <memory>
#include <random>
#include <unordered_set>
#include <optional>
#include <cassert>
#include <vector>

#include <util.h>
#include <choice.h>
#include <player.h>
#include <referee.h>
#include <writer.h>

// GameBuilder Forward declaration
template<class, class>
class GameBuilder;

// Game is an object which can be created by GameBuilder
template <class PlayerCom, class PlayerHuman, class C=Choice>
class Game final {

public:
    Game() = delete;                       // disable default constructor
    Game(const Game&) = delete;            // disable copy-constructor
    Game& operator=(const Game&) = delete; // disable copy-assignment

    auto run() {
        for(;m_rounds;m_rounds--){
            const auto com_move = m_com.play();
            const auto human_move = m_human.play();

            auto winner_move = m_referee.winner(com_move, human_move);
            auto winner_name = !winner_move.has_value() ? std::nullopt : std::make_optional(winner_move == com_move ? m_com.name() : m_human.name());

            if (winner_move.has_value() && winner_move.value() == com_move)
                m_com_win++;
            if (winner_move.has_value() && winner_move.value() == human_move)
                m_human_win++;

            m_writer.write(com_move, human_move, winner_move, winner_name, *this);

            this->m_history.push_back({com_move, human_move});
        }
    }

private:
    // Friend classes
    friend class GameBuilder<PlayerCom, PlayerHuman>;
    friend class Writer<Stdout, C>;
    // Constructor is private so that we cannot create it except from GameBuilder
    Game(PlayerCom com, PlayerHuman human, int rounds):m_com(com), m_human(human), m_rounds(rounds) {
        m_history.reserve(rounds);
    }

    PlayerCom m_com;
    PlayerHuman m_human;
    Referee<C> m_referee;
    Writer<Stdout, C> m_writer;

    int m_rounds = 1;
    int m_com_win = 0;
    int m_human_win = 0;

    std::vector<std::pair<Choice, Choice>> m_history;
};

// GameBuilder is a builder to build a game object
template <class PlayerCom, class PlayerHuman>
class GameBuilder final {
public:
    auto computer(const PlayerCom& p1) -> GameBuilder& {
        this->m_com = p1;
        return *this;
    }

    auto human(const PlayerHuman& p2) -> GameBuilder& {
        this->m_human = p2;
        return *this;
    }

    auto rounds(int rounds) -> GameBuilder& {
        assert(rounds>0);
        this->m_rounds = rounds;

        return *this;
    }

    auto build() -> Game<PlayerCom, PlayerHuman> {
        assert(m_com.has_value());
        assert(m_human.has_value());

        return Game (m_com.value(), m_human.value(), m_rounds);
    }

private:
    std::optional<PlayerCom> m_com;
    std::optional<PlayerHuman> m_human;
    int m_rounds = 1;
};

#endif
