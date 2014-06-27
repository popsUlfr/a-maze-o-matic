#include "aihuman.hpp"
#include "mazeplayground.hpp"
#include "actor.hpp"

void AIHuman::keyHandler(uint16_t key){
    switch(key){
        case TB_KEY_ARROW_UP:
            if(!(_mp->collisionN(_actor->getPosition()))){
                _actor->setPosition(_mp->getMaze().cellNPos(_actor->getPosition()));
                _actor->notifyObserver(*_actor);
            }
            break;
        case TB_KEY_ARROW_DOWN:
            if(!(_mp->collisionS(_actor->getPosition()))){
                _actor->setPosition(_mp->getMaze().cellSPos(_actor->getPosition()));
                _actor->notifyObserver(*_actor);
            }
            break;
        case TB_KEY_ARROW_LEFT:
            if(!(_mp->collisionW(_actor->getPosition()))){
                _actor->setPosition(_mp->getMaze().cellWPos(_actor->getPosition()));
                _actor->notifyObserver(*_actor);
            }
            break;
        case TB_KEY_ARROW_RIGHT:
            if(!(_mp->collisionE(_actor->getPosition()))){
                _actor->setPosition(_mp->getMaze().cellEPos(_actor->getPosition()));
                _actor->notifyObserver(*_actor);
            }
            break;
        default: ;
    }
}

void AIHuman::run(const MazePlayground* mp,Actor* actor){
    if(mp==nullptr || actor==nullptr)
        return;
    _mp=mp;
    _actor=actor;
    _running.store(true);
}

void AIHuman::stop(){
    _running.store(false);
}

void AIHuman::update(struct tb_event& event){
    if(isRunning() && event.type==TB_EVENT_KEY){
        keyHandler(event.key);
    }
}

void AIHuman::resetAI(){

}

