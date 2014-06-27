#ifndef _AIHUMAN_HPP
#define _AIHUMAN_HPP

#include "ai.hpp"
#include "termbox.hpp"

class AIHuman: public AI{
public:
    AIHuman(const Termbox &tb):_tb(tb){}
    virtual void run(const MazePlayground* mp,Actor* actor);
    virtual void stop();
protected:
    virtual void keyHandler(const MazePlayground* mp,Actor* actor,uint16_t key);
    
    const Termbox& _tb;
};
#endif