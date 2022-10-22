#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include <iostream>
#include <string_view>

#include <choice.h>
#include <util.h>

struct Human;
struct Computer;

// Player is a generic class that has name() and play() methods
template<class T, class C=Choice>
class Player {
public:
    auto name() -> std::string_view;
    auto play() -> C;
};

// Template partial specialization for Player<Human>
template<>
class Player<Human, Choice> {
public:
    auto name () -> std::string_view {
        return "Human Player";
    }

    auto play() -> Choice {
        std::string c;
        for(;;){
            std::cout << "Pick either paper, rock or scissors (p/r/s):";
            std::cin >> c;
            switch (c[0]) {
            case 'P':
            case 'p':
                return Choice::Paper;
            case 'R':
            case 'r':
                return Choice::Rock;
            case 'S':
            case 's':
                return Choice::Scissors;
            default:
                std::cout << "Warning: Invalid input" << std::endl;
            }
        }
    }
};

// Template partial specialization for Player<Computer>
template<>
class Player<Computer, Choice> {
public:
	auto play() -> Choice {
		std::default_random_engine rng(std::random_device{}());
		std::uniform_int_distribution<int16_t> dist(1, 3);
		return static_cast<Choice>(dist(rng));
	}

    auto name() -> std::string_view {
        return "Computer player";
    }
};

#endif
