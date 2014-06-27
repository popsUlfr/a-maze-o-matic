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
#ifndef _AICPU_HPP
#define _AICPU_HPP

#include "ai.hpp"
#include "mazesolution.hpp"
#include "mazeplayground.hpp"

#include <chrono>
#include <atomic>

#define AICPU_DELAY_MILLI 250

class AICpu: public AI{
public:
    AICpu(std::chrono::milliseconds delay=std::chrono::milliseconds(AICPU_DELAY_MILLI)){_delay.store(delay);}
    virtual void run(const MazePlayground* mp,Actor* actor);
    virtual void stop();
    
    virtual std::chrono::milliseconds getDelay() const{
        return _delay.load();
    }
    
    virtual void setDelay(std::chrono::milliseconds delay){
        _delay.store(delay);
    }
    
    virtual void resetAI();
protected:
    virtual unsigned int fillPossiblePaths(const MazePlayground& mp,
                                          unsigned int pos,
                                          unsigned int paths[4]);
    virtual unsigned int fillBacktrackPaths(const MazeSolution& ms,
                                           unsigned int pos,
                                           unsigned int size,
                                           const unsigned int paths[4],
                                           unsigned int outPaths[4]);
    virtual void setBacktrack(MazeSolution& ms,
                             unsigned int src,
                             unsigned int dst);
    virtual void setSolution(MazeSolution& ms,
                            unsigned int src,
                            unsigned int dst);
    virtual void clearSolution(MazeSolution& ms,
                              unsigned int src,
                              unsigned int dst);
    
    std::atomic<std::chrono::milliseconds> _delay;
};
#endif