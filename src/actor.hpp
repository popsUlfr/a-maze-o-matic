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
#ifndef _ACTOR_HPP
#define _ACTOR_HPP

#include "ai.hpp"
#include "observable.hpp"
#include "termbox.hpp"

#include <cstdint>

class MazePlayground;

class Actor:public Observable<Actor>{
public:
    static const uint32_t ACTOR_DEF_SYMBOL=0x263B;
    static const uint16_t ACTOR_DEF_COLOR=TB_RED|TB_BOLD;
    
    Actor(AI &ai,uint32_t playerSymbol=ACTOR_DEF_SYMBOL,uint16_t playerColor=ACTOR_DEF_COLOR)
    :_ai(ai),_pos(0),_prevPos(0),_playerSymbol(playerSymbol),_playerColor(playerColor),
    _score(0){}
    virtual ~Actor(){}
    
    virtual AI& getAI(){return _ai;}
    
    virtual void run(const MazePlayground* mp){
        if(mp==nullptr) return;
        _ai.run(mp,this);
    }
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
    
    virtual void setPlayerSymbol(uint32_t symbol){
        _playerSymbol=symbol;
    }
    
    virtual void setPlayerColor(uint16_t color){
        _playerColor=color;
    }
    virtual uint32_t getPlayerSymbol() const{
        return _playerSymbol;
    }
    
    virtual uint16_t getPlayerColor() const{
        return _playerColor;
    }
    
    virtual unsigned int getScore() const{
        return _score;
    }
    
    virtual void setScore(unsigned int score){
        _score=score;
    }
    
protected:
    AI &_ai;
    unsigned int _pos;
    unsigned int _prevPos;
    unsigned int _goal;
    uint32_t _playerSymbol;
    uint16_t _playerColor;
    unsigned int _score;
};
#endif