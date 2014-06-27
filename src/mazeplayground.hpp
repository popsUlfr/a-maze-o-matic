#ifndef _MAZEPLAYGROUND_HPP
#define _MAZEPLAYGROUND_HPP

#include "maze.hpp"

class Actor;

class MazePlayground{
public:
    explicit MazePlayground(const Maze &maze):_maze(maze){posRandomizer();}
    MazePlayground(const MazePlayground& mp):
    _maze(mp._maze),_start(mp._start),_end(mp._end){}
    virtual ~MazePlayground(){}
    
    virtual const Maze& getMaze() const{return _maze;}
    
    virtual void posRandomizer();
    virtual unsigned int getPosStart() const{return _start;}
    virtual unsigned int getPosEnd() const{return _end;}
    
    virtual void addActorStart(Actor &actor);
    virtual void addActorEnd(Actor &actor);
    
    virtual bool collisionNCell(Maze::Cell c) const{
        return _maze.hasWallN(c) ||
        _maze.hasBorderN(c);
    }
    virtual bool collisionN(unsigned int pos) const{return collisionNCell(_maze.getCellByPos(pos));}
    virtual bool collisionN(unsigned int x,unsigned int y) const{return collisionNCell(_maze.getCellAt(x,y));}
    
    virtual bool collisionECell(Maze::Cell c) const{
        return _maze.hasWallE(c) ||
        _maze.hasBorderE(c);
    }
    virtual bool collisionE(unsigned int pos) const{return collisionECell(_maze.getCellByPos(pos));}
    virtual bool collisionE(unsigned int x,unsigned int y) const{return collisionECell(_maze.getCellAt(x,y));}
    
    virtual bool collisionSCell(Maze::Cell c) const{
        return _maze.hasWallS(c) ||
        _maze.hasBorderS(c);
    }
    virtual bool collisionS(unsigned int pos) const{return collisionSCell(_maze.getCellByPos(pos));}
    virtual bool collisionS(unsigned int x,unsigned int y) const{return collisionSCell(_maze.getCellAt(x,y));}
    
    virtual bool collisionWCell(Maze::Cell c) const{
        return _maze.hasWallW(c) ||
        _maze.hasBorderW(c);
    }
    virtual bool collisionW(unsigned int pos) const{return collisionWCell(_maze.getCellByPos(pos));}
    virtual bool collisionW(unsigned int x,unsigned int y) const{return collisionWCell(_maze.getCellAt(x,y));}
protected:
    const Maze &_maze;
    unsigned int _start;
    unsigned int _end;
};
#endif