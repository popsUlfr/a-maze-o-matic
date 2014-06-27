#ifndef _MAZEGAME_HPP
#define _MAZEGAME_HPP

#include "termbox.hpp"
#include "actor.hpp"
#include "aicpu.hpp"

#include "observer.hpp"

class Maze;
class MazePlayground;
class Actor;
class AI;

class MazeGame:public Observer{
public:
    static const int MazeMargin;
    static const int MinimalScreenSize;
    MazeGame(Termbox &tb);
    virtual ~MazeGame();
    virtual void run();
    
    virtual void update();
    
protected:
    virtual void createMaze();
    virtual void deleteMaze();
    
    Termbox &_tb;
    Maze* _maze;
    MazePlayground* _mp;
    AICpu _humanAI;
    Actor _player;
};
#endif