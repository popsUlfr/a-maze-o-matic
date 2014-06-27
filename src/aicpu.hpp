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