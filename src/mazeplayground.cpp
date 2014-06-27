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
#include "mazeplayground.hpp"
#include "actor.hpp"

#include <random>

void MazePlayground::posRandomizer(){
    std::random_device rd;
    std::default_random_engine re(rd());
    std::uniform_int_distribution<unsigned int> uniDistEdge(0,3);
    unsigned int edge=uniDistEdge(rd);
    if((edge%2)==0){
        std::uniform_int_distribution<unsigned int> uniDistWidth(0,_maze->getWidth()-1);
        _start=_maze->coordToPos(uniDistWidth(rd),(edge==0)?0:_maze->getHeight()-1);
        _end=_maze->coordToPos(uniDistWidth(rd),(edge==0)?_maze->getHeight()-1:0);
    }
    else{
        std::uniform_int_distribution<unsigned int> uniDistHeight(0,_maze->getHeight()-1);
        _start=_maze->coordToPos((edge==1)?0:_maze->getWidth()-1,uniDistHeight(rd));
        _end=_maze->coordToPos((edge==1)?_maze->getWidth()-1:0,uniDistHeight(rd));
    }
}

void MazePlayground::addActorStart(Actor &actor){
    actor.resetPosition(getPosStart());
    actor.setGoalPosition(getPosEnd());
}

void MazePlayground::addActorEnd(Actor &actor){
    actor.resetPosition(getPosEnd());
    actor.setGoalPosition(getPosStart());
}
