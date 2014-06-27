/*
 * Copyright (c) 2014 Philipp Richter
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "aihuman.hpp"
#include "mazeplayground.hpp"
#include "actor.hpp"

void AIHuman::keyHandler(uint16_t key){
    switch(key){
        case ARROW_UP:
            if(!(_mp->collisionN(_actor->getPosition()))){
                _actor->setPosition(_mp->getMaze().cellNPos(_actor->getPosition()));
                _actor->notifyObserver(*_actor);
            }
            break;
        case ARROW_DOWN:
            if(!(_mp->collisionS(_actor->getPosition()))){
                _actor->setPosition(_mp->getMaze().cellSPos(_actor->getPosition()));
                _actor->notifyObserver(*_actor);
            }
            break;
        case ARROW_LEFT:
            if(!(_mp->collisionW(_actor->getPosition()))){
                _actor->setPosition(_mp->getMaze().cellWPos(_actor->getPosition()));
                _actor->notifyObserver(*_actor);
            }
            break;
        case ARROW_RIGHT:
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

