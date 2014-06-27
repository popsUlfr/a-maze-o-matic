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
#ifndef _AIHUMAN_HPP
#define _AIHUMAN_HPP

#include "ai.hpp"
#include "termbox.hpp"
#include "observer.hpp"

#define ARROW_UP 0xFFED
#define ARROW_DOWN 0xFFEC
#define ARROW_LEFT 0xFFEB
#define ARROW_RIGHT 0xFFEA

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