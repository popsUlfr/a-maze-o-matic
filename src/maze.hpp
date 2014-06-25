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
    Maze(unsigned int width, unsigned int height);
    virtual ~Maze(){}
    
    unsigned int getWidth(){return _width;}
    unsigned int getHeight(){return _height;}
    
    Cell& getCellAt(unsigned int x,unsigned int y){
        return _map.at(coordToPos(x,y));
    }
    
    Cell& getCellByPos(unsigned int i){
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
    
    unsigned int coordToPos(unsigned int x,unsigned int y) const{return (y*_width)+x;}
    unsigned int posToCoordX(unsigned int pos) const{return pos%_width;}
    unsigned int posToCoordY(unsigned int pos) const{return pos/_width;}
    
    int cellNPos(unsigned int pos) const{return (pos>=_width)?pos-_width:-1;}
    int cellEPos(unsigned int pos) const{return ((pos%_width)<_width-1)?pos+1:-1;}
    int cellSPos(unsigned int pos) const{return ((pos/_width)<_height-1)?pos+_width:-1;}
    int cellWPos(unsigned int pos) const{return ((pos%_width)>0)?pos-1:-1;}
    
    void printMaze();
protected:
    void reinitStructure(){
        _map.resize(getWidth()*getHeight(),MAZE_WALL_ALL);
        depthFirstSearchAlgorithm();
    }
    unsigned int fillNeighbours (unsigned int pos, unsigned int nbCells[4]) const;
    void knockDownWall(unsigned int src,unsigned int dst);
    void fillBorders(unsigned int pos);
    void depthFirstSearchAlgorithm();
    
    const unsigned int _width;
    const unsigned int _height;
    std::vector<Cell> _map;
};
#endif