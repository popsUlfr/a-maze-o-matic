#ifndef _TERMBOX_HPP
#define _TERMBOX_HPP

#include <stdexcept>
#include <string>

#include "maze.hpp"

class Termbox{
public:
    explicit Termbox();
    virtual ~Termbox();
    void run();
protected:
    void drawMazeCell(Maze &maze,int tlx,int tly,unsigned int x,unsigned int y,uint16_t color);
    void drawMazeFrame(Maze &maze,int tlx,int tly,unsigned int x,unsigned int y,uint16_t color);
    void drawPrettyJunctions(Maze &maze,int tlx,int tly,unsigned int x,unsigned y,uint16_t color);
    void drawMazeDoor(Maze &maze,int tlx, int tly,unsigned int x,unsigned y,uint32_t mazeDoorSymbol,uint16_t color,uint16_t bg);
    void drawMaze(int tlx,int tly,int brx,int bry,uint16_t color);
    void drawScreen();
    void drawRectangle(int tlx,int tly,int brx,int bry,uint16_t color);
};

class TermboxInitException: public std::runtime_error{
public:
    explicit TermboxInitException(int code);
    static std::string errorStringCreator(int code);
    int getErrorCode(){return _code;}
private:
    int _code;
};
#endif