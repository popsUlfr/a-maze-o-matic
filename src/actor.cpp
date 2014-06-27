#include "actor.hpp"
#include "mazeplayground.hpp"

void Actor::run(const MazePlayground* mp){
    if(mp==nullptr) return;
    _ai.run(mp,this);
}

