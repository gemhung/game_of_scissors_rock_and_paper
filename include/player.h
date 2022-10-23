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
    Player();
    Player(const std::string& name);
    auto name() -> std::string_view;
    auto play() -> C;
private:
    std::string m_name;
};

// Implement Player template specialization for Human
template<>
class Player<Human, Choice> {
public:
    Player():m_name("Human Player"){}
    Player(const std::string& name):m_name(name) {};

    auto name() -> std::string_view {
        return m_name;
    };

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
private:
    std::string m_name;
};

// Implement Player template specialization for Computer
template<>
class Player<Computer, Choice> {
public:
    Player():m_name("Computer Player"){}
    Player(const std::string& name):m_name(name) {};

    auto name() -> std::string_view {
        return m_name;
    };
	auto play() -> Choice {
		std::default_random_engine rng(std::random_device{}());
		std::uniform_int_distribution<int16_t> dist(1, 3);
		return static_cast<Choice>(dist(rng));
	}

private:
    std::string m_name;
};

#endif
