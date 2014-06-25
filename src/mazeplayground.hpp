#ifndef _MAZEPLAYGROUND_HPP
#define _MAZEPLAYGROUND_HPP

#include "maze.hpp"

class MazePlayground{
public:
    MazePlayground(Maze &maze):_maze(maze){posRandomizer();}
    Maze& getMaze(){return _maze;}
    
    void posRandomizer();
    unsigned int getPosStart(){return _start;}
    unsigned int getPosEnd(){return _end;}
    
protected:    
    Maze &_maze;
    unsigned int _start;
    unsigned int _end;
};
#endif