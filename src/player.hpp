#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include "actor.hpp"
#include "observer.hpp"
#include "termbox.hpp"
#include "aihuman.hpp"

class Player:public Actor,public Observer<struct tb_event&>{
public:
    explicit Player():Actor(_ai){}
    virtual ~Player(){}
    
    virtual void update(struct tb_event& event){
        _ai.update(event);}
protected:
    AIHuman _ai;
};
#endif