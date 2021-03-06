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
#ifndef _MAZE_HPP
#define _MAZE_HPP

#include <vector>
#include <cstdint>

#define MAZE_WALL_NORTH 0x01
#define MAZE_WALL_EAST 0x02
#define MAZE_WALL_SOUTH 0x04
#define MAZE_WALL_WEST 0x08

#define MAZE_WALL_ALL ( MAZE_WALL_NORTH | MAZE_WALL_EAST | MAZE_WALL_SOUTH | MAZE_WALL_WEST )

#define MAZE_BORDER_NORTH 0x10
#define MAZE_BORDER_EAST 0x20
#define MAZE_BORDER_SOUTH 0x40
#define MAZE_BORDER_WEST 0x80

#define MAZE_CORNER_SYMBOL "*"
#define MAZE_JUNCTION_SYMBOL "+"
#define MAZE_VERTICAL_WALL_SYMBOL "|"
#define MAZE_HORIZONTAL_WALL_SYMBOL "---"
#define MAZE_CELL_SPACE "   "
#define MAZE_JUNCTION_SPACE " "

/**
 * A Maze class implementing the Depth-First Search algorithm
 */
class Maze{
public:
    typedef uint8_t Cell;
    
    /**
     * The maze is represented as a list of Cells
     * The Cells can have up to 4 walls and 4 borders
     */
    explicit Maze(unsigned int width, unsigned int height)
    :_width(width),_height(height),
    _map(width*height,MAZE_WALL_ALL){depthFirstSearchAlgorithm();}
    Maze(const Maze& maze):
    _width(maze._width),_height(maze._height),_map(maze._map){}
    
    virtual ~Maze(){}
    
    virtual unsigned int getWidth() const{return _width;}
    virtual unsigned int getHeight() const{return _height;}
    
    virtual unsigned int getAmountOfCells() const{return _width*_height;}
    
    virtual Cell& getCellAt(unsigned int x,unsigned int y){
        return _map.at(coordToPos(x,y));
    }
    virtual Cell getCellAt(unsigned int x,unsigned int y) const{
        return _map.at(coordToPos(x,y));
    }
    virtual Cell& getCellByPos(unsigned int i){
        return _map.at(i);
    }
    virtual Cell getCellByPos(unsigned int i) const{
        return _map.at(i);
    }
    static bool hasWallN(Cell c){return (c & MAZE_WALL_NORTH)==MAZE_WALL_NORTH;}
    static bool hasWallE(Cell c){return (c & MAZE_WALL_EAST)==MAZE_WALL_EAST;}
    static bool hasWallS(Cell c){return (c & MAZE_WALL_SOUTH)==MAZE_WALL_SOUTH;}
    static bool hasWallW(Cell c){return (c & MAZE_WALL_WEST)==MAZE_WALL_WEST;}
    
    static bool hasBorderN(Cell c){return (c & MAZE_BORDER_NORTH)==MAZE_BORDER_NORTH;}
    static bool hasBorderE(Cell c){return (c & MAZE_BORDER_EAST)==MAZE_BORDER_EAST;}
    static bool hasBorderS(Cell c){return (c & MAZE_BORDER_SOUTH)==MAZE_BORDER_SOUTH;}
    static bool hasBorderW(Cell c){return (c & MAZE_BORDER_WEST)==MAZE_BORDER_WEST;}
    
    virtual unsigned int coordToPos(unsigned int x,unsigned int y) const{return (y*_width)+x;}
    virtual unsigned int posToCoordX(unsigned int pos) const{return pos%_width;}
    virtual unsigned int posToCoordY(unsigned int pos) const{return pos/_width;}
    
    virtual int cellNPos(unsigned int pos) const{return (pos>=_width)?pos-_width:-1;}
    virtual int cellEPos(unsigned int pos) const{return ((pos%_width)<_width-1)?pos+1:-1;}
    virtual int cellSPos(unsigned int pos) const{return ((pos/_width)<_height-1)?pos+_width:-1;}
    virtual int cellWPos(unsigned int pos) const{return ((pos%_width)>0)?pos-1:-1;}
    
    virtual void printMaze();
protected:
    virtual void reinitStructure(){
        _map.resize(getWidth()*getHeight(),MAZE_WALL_ALL);
        depthFirstSearchAlgorithm();
    }
    virtual unsigned int fillNeighbours (unsigned int pos, unsigned int nbCells[4]) const;
    virtual void knockDownWall(unsigned int src,unsigned int dst);
    virtual void fillBorders(unsigned int pos);
    virtual void depthFirstSearchAlgorithm();
    
    unsigned int _width;
    unsigned int _height;
    std::vector<Cell> _map;
};
#endif