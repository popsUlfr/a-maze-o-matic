#include "aihuman.hpp"
#include "mazeplayground.hpp"
#include "actor.hpp"

void AIHuman::keyHandler(const MazePlayground* mp,Actor* actor,uint16_t key){
    switch(key){
        case TB_KEY_ARROW_UP:
            if(!(mp->collisionN(actor->getPosition()))){
                actor->setPosition(mp->getMaze().cellNPos(actor->getPosition()));
                actor->notifyObserver();
            }
            break;
        case TB_KEY_ARROW_DOWN:
            if(!(mp->collisionS(actor->getPosition()))){
                actor->setPosition(mp->getMaze().cellSPos(actor->getPosition()));
                actor->notifyObserver();
            }
            break;
        case TB_KEY_ARROW_LEFT:
            if(!(mp->collisionW(actor->getPosition()))){
                actor->setPosition(mp->getMaze().cellWPos(actor->getPosition()));
                actor->notifyObserver();
            }
            break;
        case TB_KEY_ARROW_RIGHT:
            if(!(mp->collisionE(actor->getPosition()))){
                actor->setPosition(mp->getMaze().cellEPos(actor->getPosition()));
                actor->notifyObserver();
            }
            break;
        default: ;
    }
}

void AIHuman::run(const MazePlayground* mp,Actor* actor){
    if(mp==nullptr || actor==nullptr) return;
    struct tb_event ev;
    bool cont=true;
    for(;cont;){
        int type=_tb.poll_event(&ev);
        switch(type){
            case TB_EVENT_KEY:
                if(ev.key==TB_KEY_ESC)
                    cont=false;
                else
                    keyHandler(mp,actor,ev.key);
                break;
            default: ;
        }
    }
}

void AIHuman::stop(){

}

