#include "actor.hpp"
#include "mazeplayground.hpp"

void Actor::run(const MazePlayground* mp){
    if(mp==nullptr || _ai==nullptr) return;
    _prevPos=_pos=mp->getPosStart();
    _ai->run(mp,this);
}

void Actor::stop(){

}

