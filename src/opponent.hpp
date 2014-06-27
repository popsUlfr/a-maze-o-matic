#ifndef _OPPONENT_HPP
#define _OPPONENT_HPP

#include "aicpu.hpp"
#include "actor.hpp"

class Opponent:public Actor{
public:
    Opponent():Actor(_ai){}
    virtual ~Opponent(){}
    
protected:
    AICpu _ai;
};
#endif