#ifndef _ACTOR_HPP
#define _ACTOR_HPP

#include "ai.hpp"
#include "observable.hpp"

class MazePlayground;

class Actor:public Observable{
public:
    Actor(AI *ai):_ai(ai),_pos(0),_prevPos(0){}
    virtual ~Actor(){}
    
    virtual AI* getAI() const{return _ai;}
    virtual void setAI(AI* ai){_ai=ai;}
    
    virtual void run(const MazePlayground* mp);
    virtual void stop();
    
    virtual void resetPosition(unsigned int pos){
        _prevPos=_pos=pos;
    }
    virtual void setPosition(unsigned int pos){
        _prevPos=_pos;
        _pos=pos;
    }
    virtual unsigned int getPosition() const{return _pos;}
    virtual unsigned int getPrevPosition() const{return _prevPos;}
protected:
    AI *_ai;
    unsigned int _pos;
    unsigned int _prevPos;
};
#endif