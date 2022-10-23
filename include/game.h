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
template<class, class, class, class>
class GameBuilder;

// Game is an object which can be created by GameBuilder
//template <class PlayerCom, class PlayerHuman, class C=Choice, class W=Writer<Stdout>>
template <class PlayerCom, class PlayerHuman, class C, class W>
class Game final {

public:
    Game(PlayerCom com, PlayerHuman human, int rounds):m_com(com), m_human(human), m_rounds(rounds) {
        m_play_history.reserve(rounds);
    }

    Game() = delete;                       // disable default constructor
    Game(const Game&) = delete;            // disable copy-constructor
    Game& operator=(const Game&) = delete; // disable copy-assignment

    // run() will run until m_rounds become zero
    auto run() {
        for(;m_rounds;m_rounds--){
            const auto com_move = m_com.play();
            const auto human_move = m_human.play();

            const auto winner_move = m_referee.winner(com_move, human_move);
            const auto winner_name = !winner_move.has_value() ? std::nullopt : std::make_optional(winner_move == com_move ? m_com.name() : m_human.name());

            this->m_play_history.push_back({com_move, human_move});
            this->m_winner_history.push_back({winner_move, winner_name});

            m_writer.write(*this);
        }
    }

    auto play_history() -> const std::vector<std::pair<Choice, Choice>>& { 
        return m_play_history;
    };

    auto winner_history() -> const std::vector<std::pair<std::optional<Choice>, std::optional<std::string_view>>>&{
        return m_winner_history;
    };

    auto left_rounds() -> int {
        return m_rounds;
    }

private:
    friend class Writer<Stdout>;
    friend class Writer<Dummy>;

    PlayerCom m_com;
    PlayerHuman m_human;
    Referee<C> m_referee;
    W m_writer;

    int m_rounds = 1;

    std::vector<std::pair<Choice, Choice>> m_play_history;
    std::vector<std::pair<std::optional<Choice>, std::optional<std::string_view>>> m_winner_history;
};

// GameBuilder is a builder to build a game object
template <class PlayerCom, class PlayerHuman, class C=Choice, class W=Writer<Stdout>>
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

    auto build() -> Game<PlayerCom, PlayerHuman, C, W> {
        assert(m_com.has_value());
        assert(m_human.has_value());

        return Game<PlayerCom, PlayerHuman, C, W>(m_com.value(), m_human.value(), m_rounds);
    }

private:
    std::optional<PlayerCom> m_com;
    std::optional<PlayerHuman> m_human;
    int m_rounds = 1;
};

#endif
