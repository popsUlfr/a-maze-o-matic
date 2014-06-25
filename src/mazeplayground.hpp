#ifndef _MAZEPLAYGROUND_HPP
#define _MAZEPLAYGROUND_HPP

#include "maze.hpp"

class MazePlayground{
public:
    MazePlayground(Maze &maze):_maze(maze){posRandomizer();}
    Maze& getMaze() const{return _maze;}
    
    void posRandomizer();
    unsigned int getPosStart() const{return _start;}
    unsigned int getPosEnd() const{return _end;}
    unsigned int getCurrPos() const{return _currPos;}
    unsigned int getPrevPos() const{return _prevPos;}
    
    bool collisionN(unsigned int x,unsigned int y) const{
        return _maze.hasWallN(_maze.getCellAt(x,y)) ||
        _maze.hasBorderN(_maze.getCellAt(x,y));
    }
    bool collisionE(unsigned int x,unsigned int y) const{
        return _maze.hasWallE(_maze.getCellAt(x,y)) ||
        _maze.hasBorderE(_maze.getCellAt(x,y));
    }
    bool collisionS(unsigned int x,unsigned int y) const{
        return _maze.hasWallS(_maze.getCellAt(x,y)) ||
        _maze.hasBorderS(_maze.getCellAt(x,y));
    }
    bool collisionW(unsigned int x,unsigned int y) const{
        return _maze.hasWallW(_maze.getCellAt(x,y)) ||
        _maze.hasBorderW(_maze.getCellAt(x,y));
    }
    
    bool movePlayerN() {
        int pos;
        if(!collisionN(_maze.posToCoordX(_currPos),_maze.posToCoordY(_currPos)) &&
                (pos=_maze.cellNPos(_currPos))>=0) {
            _prevPos=_currPos; _currPos=pos;
            return true;
        }
        else
            return false;
    }
    bool movePlayerE() {
        int pos;
        if(!collisionE(_maze.posToCoordX(_currPos),_maze.posToCoordY(_currPos)) &&
                (pos=_maze.cellEPos(_currPos))>=0) {
            _prevPos=_currPos; _currPos=pos;
            return true;
        }
        else
            return false;
    }
    bool movePlayerS() {
        int pos;
        if(!collisionS(_maze.posToCoordX(_currPos),_maze.posToCoordY(_currPos)) &&
                (pos=_maze.cellSPos(_currPos))>=0) {
            _prevPos=_currPos; _currPos=pos;
            return true;
        }
        else
            return false;
    }
    bool movePlayerW() {
        int pos;
        if(!collisionW(_maze.posToCoordX(_currPos),_maze.posToCoordY(_currPos)) &&
                (pos=_maze.cellWPos(_currPos))>=0) {
            _prevPos=_currPos; _currPos=pos;
            return true;
        }
        else
            return false;
    }
    
protected:
    Maze &_maze;
    unsigned int _start;
    unsigned int _end;
    unsigned int _prevPos;
    unsigned int _currPos;
};
#endif