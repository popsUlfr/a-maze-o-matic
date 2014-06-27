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
#ifndef _MAZEPLAYGROUND_HPP
#define _MAZEPLAYGROUND_HPP

#include "maze.hpp"

class Actor;

class MazePlayground{
public:
    explicit MazePlayground(Maze &maze):_maze(&maze){posRandomizer();}
    MazePlayground(const MazePlayground& mp):
    _maze(mp._maze),_start(mp._start),_end(mp._end){}
    virtual ~MazePlayground(){}
    
    virtual Maze& getMaze(){return *_maze;}
    virtual const Maze& getMaze() const{return *_maze;}
    
    virtual void posRandomizer();
    virtual unsigned int getPosStart() const{return _start;}
    virtual unsigned int getPosEnd() const{return _end;}
    
    virtual void addActorStart(Actor &actor);
    virtual void addActorEnd(Actor &actor);
    
    virtual bool collisionNCell(Maze::Cell c) const{
        return _maze->hasWallN(c) ||
        _maze->hasBorderN(c);
    }
    virtual bool collisionN(unsigned int pos) const{return collisionNCell(_maze->getCellByPos(pos));}
    virtual bool collisionN(unsigned int x,unsigned int y) const{return collisionNCell(_maze->getCellAt(x,y));}
    
    virtual bool collisionECell(Maze::Cell c) const{
        return _maze->hasWallE(c) ||
        _maze->hasBorderE(c);
    }
    virtual bool collisionE(unsigned int pos) const{return collisionECell(_maze->getCellByPos(pos));}
    virtual bool collisionE(unsigned int x,unsigned int y) const{return collisionECell(_maze->getCellAt(x,y));}
    
    virtual bool collisionSCell(Maze::Cell c) const{
        return _maze->hasWallS(c) ||
        _maze->hasBorderS(c);
    }
    virtual bool collisionS(unsigned int pos) const{return collisionSCell(_maze->getCellByPos(pos));}
    virtual bool collisionS(unsigned int x,unsigned int y) const{return collisionSCell(_maze->getCellAt(x,y));}
    
    virtual bool collisionWCell(Maze::Cell c) const{
        return _maze->hasWallW(c) ||
        _maze->hasBorderW(c);
    }
    virtual bool collisionW(unsigned int pos) const{return collisionWCell(_maze->getCellByPos(pos));}
    virtual bool collisionW(unsigned int x,unsigned int y) const{return collisionWCell(_maze->getCellAt(x,y));}
protected:
    Maze *_maze;
    unsigned int _start;
    unsigned int _end;
};
#endif