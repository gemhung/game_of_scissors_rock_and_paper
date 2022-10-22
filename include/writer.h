#ifndef WRITER_HEADER
#define WRITER_HEADER

#include <iostream>
#include <optional>

using std::cout;
using std::endl;

template<class, class, class>
class Game;

template<class W, class C>
class Writer{
public:
    template<class PlayerCom, class PlayerHuman>
    auto write(C com_move, C human_move, std::optional<C> winner_move, std::optional<std::string_view> winner_name, Game<PlayerCom, PlayerHuman, C>& game);
};

struct Stdout;

template<class C>
class Writer<Stdout, C> {
public:
    template<class PlayerCom, class PlayerHuman>
    auto write(C com_move, C human_move, std::optional<C> winner_move, std::optional<std::string_view> winner_name, Game<PlayerCom, PlayerHuman, C>& game){

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

#endif
