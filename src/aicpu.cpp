#include "aicpu.hpp"
#include "mazeplayground.hpp"
#include "actor.hpp"
#include "mazesolution.hpp"

#include <stack>
#include <random>
#include <chrono>
#include <thread>

unsigned int AICpu::fillPossiblePaths(const MazePlayground& mp,
                                     unsigned int pos,
                                     unsigned int paths[4]) {
    unsigned int nb=0;
    if(!(mp.collisionN(pos)))
        paths[nb++]=mp.getMaze().cellNPos(pos);
    if(!(mp.collisionE(pos)))
        paths[nb++]=mp.getMaze().cellEPos(pos);
    if(!(mp.collisionS(pos)))
        paths[nb++]=mp.getMaze().cellSPos(pos);
    if(!(mp.collisionW(pos)))
        paths[nb++]=mp.getMaze().cellWPos(pos);
    return nb;
}

unsigned int AICpu::fillBacktrackPaths(const MazeSolution& ms,
                                       unsigned int pos,
                                       unsigned int size,
                                       const unsigned int paths[4],
                                       unsigned int outPaths[4])
{
    unsigned int nb=0;
    MazeSolution::CellSolution cs=ms.getCellSolutionByPos(pos);
    for(;size>0;--size){
        if(ms.getMaze().cellNPos(pos)==(int)paths[size-1]
            && !ms.hasBacktrackN(cs))
            outPaths[nb++]=paths[size-1];
        else if(ms.getMaze().cellEPos(pos)==(int)paths[size-1]
            && !ms.hasBacktrackE(cs))
            outPaths[nb++]=paths[size-1];
        else if(ms.getMaze().cellSPos(pos)==(int)paths[size-1]
            && !ms.hasBacktrackS(cs))
            outPaths[nb++]=paths[size-1];
        else if(ms.getMaze().cellWPos(pos)==(int)paths[size-1]
            && !ms.hasBacktrackW(cs))
            outPaths[nb++]=paths[size-1];
    }
    return nb;
}

void AICpu::setBacktrack(MazeSolution& ms,
                         unsigned int src,
                         unsigned int dst){
    if(ms.getMaze().cellNPos(src)==(int)dst){
        ms.setBacktrackN(ms.getCellSolutionByPos(src));
        ms.setBacktrackS(ms.getCellSolutionByPos(dst));
    }
    else if(ms.getMaze().cellEPos(src)==(int)dst){
        ms.setBacktrackE(ms.getCellSolutionByPos(src));
        ms.setBacktrackW(ms.getCellSolutionByPos(dst));
    }
    else if(ms.getMaze().cellSPos(src)==(int)dst){
        ms.setBacktrackS(ms.getCellSolutionByPos(src));
        ms.setBacktrackN(ms.getCellSolutionByPos(dst));
    }
    else if(ms.getMaze().cellWPos(src)==(int)dst){
        ms.setBacktrackW(ms.getCellSolutionByPos(src));
        ms.setBacktrackE(ms.getCellSolutionByPos(dst));
    }
}

void AICpu::setSolution(MazeSolution& ms,
                        unsigned int src,
                        unsigned int dst)
{
    if(ms.getMaze().cellNPos(src)==(int)dst){
        ms.setSolutionN(ms.getCellSolutionByPos(src));
        ms.setSolutionS(ms.getCellSolutionByPos(dst));
    }
    else if(ms.getMaze().cellEPos(src)==(int)dst){
        ms.setSolutionE(ms.getCellSolutionByPos(src));
        ms.setSolutionW(ms.getCellSolutionByPos(dst));
    }
    else if(ms.getMaze().cellSPos(src)==(int)dst){
        ms.setSolutionS(ms.getCellSolutionByPos(src));
        ms.setSolutionN(ms.getCellSolutionByPos(dst));
    }
    else if(ms.getMaze().cellWPos(src)==(int)dst){
        ms.setSolutionW(ms.getCellSolutionByPos(src));
        ms.setSolutionE(ms.getCellSolutionByPos(dst));
    }
}

void AICpu::clearSolution(MazeSolution& ms,
                        unsigned int src,
                        unsigned int dst)
{
    if(ms.getMaze().cellNPos(src)==(int)dst){
        ms.clearSolutionN(ms.getCellSolutionByPos(src));
        ms.clearSolutionS(ms.getCellSolutionByPos(dst));
    }
    else if(ms.getMaze().cellEPos(src)==(int)dst){
        ms.clearSolutionE(ms.getCellSolutionByPos(src));
        ms.clearSolutionW(ms.getCellSolutionByPos(dst));
    }
    else if(ms.getMaze().cellSPos(src)==(int)dst){
        ms.clearSolutionS(ms.getCellSolutionByPos(src));
        ms.clearSolutionN(ms.getCellSolutionByPos(dst));
    }
    else if(ms.getMaze().cellWPos(src)==(int)dst){
        ms.clearSolutionW(ms.getCellSolutionByPos(src));
        ms.clearSolutionE(ms.getCellSolutionByPos(dst));
    }
}

void AICpu::run(const MazePlayground* mp, Actor* actor){
    if(mp==nullptr || actor==nullptr) return;
    _running.store(true);
    MazeSolution ms(mp->getMaze());
    std::stack<unsigned int> _posStack;
    
    std::random_device rd;
    std::default_random_engine re(rd());
    
    unsigned int paths[4],fPaths[4];
    
    for(;isRunning() && actor->getPosition()!=actor->getGoalPosition();){
        unsigned int nb;
        if((nb=fillPossiblePaths(*mp,actor->getPosition(),paths))>0
            && (nb=fillBacktrackPaths(ms,actor->getPosition(),nb,paths,fPaths))>0
        ){
            _posStack.push(actor->getPosition());
            unsigned int newpos;
            if(nb>1) {
                std::uniform_int_distribution<unsigned int> uniDist(0,nb-1);
                newpos=fPaths[uniDist(re)];
            }
            else
                newpos=fPaths[0];
            setBacktrack(ms,actor->getPosition(),newpos);
            setSolution(ms,actor->getPosition(),newpos);
            actor->setPosition(newpos);
        }
        else{
            if(_posStack.empty()) break;
            clearSolution(ms,_posStack.top(),actor->getPosition());
            actor->setPosition(_posStack.top());
            _posStack.pop();
        }
        actor->notifyObserver(*actor);
        std::this_thread::sleep_for(_delay.load());
    }
    
}

void AICpu::stop(){
    _running.store(false);
}

void AICpu::resetAI(){
}

