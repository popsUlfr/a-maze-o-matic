#ifndef _AIHUMAN_HPP
#define _AIHUMAN_HPP

#include "ai.hpp"
#include "termbox.hpp"
#include "observer.hpp"

class AIHuman: public AI,public Observer<struct tb_event&>{
public:
    AIHuman(){}
    virtual void run(const MazePlayground* mp,Actor* actor);
    virtual void stop();
    
    virtual void update(struct tb_event& event);
    
    virtual void resetAI();
protected:
    virtual void keyHandler(uint16_t key);
    
    const MazePlayground* _mp;
    Actor* _actor;
};
#endif