#ifndef _MAZEGAME_HPP
#define _MAZEGAME_HPP

#include "termbox.hpp"
#include "maze.hpp"
#include "mazeplayground.hpp"

class MazeGame{
public:
    static const int MazeMargin;
    static const int MinimalScreenSize;
    MazeGame(Termbox &tb):_tb(tb),_maze(nullptr),_mp(nullptr){}
    ~MazeGame();
    void run();
    
protected:
    void keyHandler(uint16_t key);
    void drawScreen();
    void updatePlayer();
    Termbox &_tb;
    Maze* _maze;
    MazePlayground* _mp;
};
#endif