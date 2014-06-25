#ifndef _AIHUMAN_HPP
#define _AIHUMAN_HPP

#include "ai.hpp"
#include "termbox.hpp"

class HumanAI: public AI{
public:
    HumanAI(const Termbox& tb){}
protected:
    const Termbox& _tb;
};
#endif