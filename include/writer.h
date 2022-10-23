#ifndef WRITER_HEADER
#define WRITER_HEADER

#include <iostream>
#include <optional>

using std::cout;
using std::endl;

// Forward declaration
template<class, class, class, class>
class Game;

// Generice Writer
template<class Target>
class Writer{
public:
    template<class PlayerCom, class PlayerHuman, class C>
    auto write(Game<PlayerCom, PlayerHuman, C, Writer<Target>>& game);
};

// Implement Writer template specialization for Stdout
struct Stdout;
template<>
class Writer<Stdout> {
public:
    template<class PlayerCom, class PlayerHuman, class C>
    auto write(Game<PlayerCom, PlayerHuman, C, Writer<Stdout>>& game){
        if(game.m_play_history.empty() || game.m_winner_history.empty())
            cout<<"Error: nothing to write to stdout cause history is empty"<<endl;

        const auto& [winner_move, winner_name] = game.m_winner_history.back();
        const auto& [com_move, human_move] = game.m_play_history.back();

        cout<<game.m_com.name()<<" has "<< to_symbol(com_move)<<endl;
        cout<<game.m_human.name()<<" has "<< to_symbol(human_move)<<endl;

        if(winner_move == com_move)
            cout<<game.m_com.name()<<" won"<<endl;
        else if(winner_move == human_move)
            cout<<game.m_human.name()<<" won"<<endl;
        else 
            cout<<"It's a draw round"<<endl;
    }
};

// Implement Writer template specialization for dummy
struct Dummy;
template<>
class Writer<Dummy> {
public:
    template<class PlayerCom, class PlayerHuman, class C> 
    auto write(Game<PlayerCom, PlayerHuman, C, Writer<Dummy>>& game){
        // write nothing since it's dummy implementation
    }
};

#endif
