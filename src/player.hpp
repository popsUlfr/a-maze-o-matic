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
#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include "actor.hpp"
#include "observer.hpp"
#include "termbox.hpp"
#include "aihuman.hpp"

class Player:public Actor,public Observer<struct tb_event&>{
public:
    explicit Player(uint32_t playerSymbol=ACTOR_DEF_SYMBOL,uint16_t playerColor=ACTOR_DEF_COLOR)
    :Actor(_ai,playerSymbol,playerColor){}
    virtual ~Player(){}
    
    virtual void update(struct tb_event& event){
        _ai.update(event);}
protected:
    AIHuman _ai;
};
#endif