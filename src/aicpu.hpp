#ifndef _AICPU_HPP
#define _AICPU_HPP

#include "ai.hpp"
#include "mazesolution.hpp"
#include "mazeplayground.hpp"

class AICpu: public AI{
public:
    AICpu(){}
    virtual void run(const MazePlayground* mp,Actor* actor);
    virtual void stop();
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
};
#endif