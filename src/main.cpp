#include <sstream>
#include <util.h>
#include <choice.h>
#include <player.h>
#include <game.h>
#include <referee.h>


int main(int argc, char** argv) {
    auto rounds = 10;
    if(argc <= 1){
        std::cout<<"Info: Using default 10 rounds"<<std::endl;
    }else {
        std::istringstream ss(argv[1]);
        if (!(ss >> rounds)) {
            std::cerr << "Invalid number: " << argv[1] << '\n';
            std::cout<<"Warning: Using default 10 rounds"<<std::endl;
        } else if (!ss.eof()) {
            std::cerr << "Trailing characters after number: " << argv[1] << '\n';
            std::cout<<"Warning: Using default 10 rounds"<<std::endl;
        }
        std::cout<<"Info: start a game with "<< rounds<< " rounds"<<endl;
    }

    auto game = GameBuilder<Player<Computer>, Player<Human>>()
        .computer(Player<Computer>())
        .human(Player<Human>())
        .rounds(rounds)
        .build();

    game.run();

	return 0;
}
