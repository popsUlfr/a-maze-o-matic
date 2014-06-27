#ifndef _ACTOR_HPP
#define _ACTOR_HPP

#include "ai.hpp"
#include "observable.hpp"

class MazePlayground;

class Actor:public Observable<Actor>{
public:
    Actor(AI &ai):_ai(ai),_pos(0),_prevPos(0){}
    virtual ~Actor(){}
    
    virtual AI& getAI(){return _ai;}
    
    virtual void run(const MazePlayground* mp);
    virtual void stop(){_ai.stop();}
    
    virtual void resetPosition(unsigned int pos){
        _prevPos=_pos=pos;
    }
    virtual void setPosition(unsigned int pos){
        _prevPos=_pos;
        _pos=pos;
    }
    virtual void setGoalPosition(unsigned int pos){
        _goal=pos;
    }
    virtual unsigned int getPosition() const{return _pos;}
    virtual unsigned int getPrevPosition() const{return _prevPos;}
    virtual unsigned int getGoalPosition() const{return _goal;}
protected:
    AI &_ai;
    unsigned int _pos;
    unsigned int _prevPos;
    unsigned int _goal;
};
#endif