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

class Maze{
public:
    typedef uint8_t Cell;
    Maze(unsigned int width, unsigned int height);
    virtual ~Maze(){}
    
    unsigned int getWidth(){return _width;}
    unsigned int getHeight(){return _height;}
    
    Cell& getCellAt(unsigned int x,unsigned int y){
        return _map.at((_width*y)+x);
    }
    bool hasWallN(Cell c){return (c & MAZE_WALL_NORTH)==MAZE_WALL_NORTH;}
    bool hasWallE(Cell c){return (c & MAZE_WALL_EAST)==MAZE_WALL_EAST;}
    bool hasWallS(Cell c){return (c & MAZE_WALL_SOUTH)==MAZE_WALL_SOUTH;}
    bool hasWallW(Cell c){return (c & MAZE_WALL_WEST)==MAZE_WALL_WEST;}
    
    bool hasBorderN(Cell c){return (c & MAZE_BORDER_NORTH)==MAZE_BORDER_NORTH;}
    bool hasBorderE(Cell c){return (c & MAZE_BORDER_EAST)==MAZE_BORDER_EAST;}
    bool hasBorderS(Cell c){return (c & MAZE_BORDER_SOUTH)==MAZE_BORDER_SOUTH;}
    bool hasBorderW(Cell c){return (c & MAZE_BORDER_WEST)==MAZE_BORDER_WEST;}
    
    void printMaze();
    void printMazeNormal();
private:
    unsigned int fillNeighbours(unsigned int pos, unsigned int nbCells[4]);
    void knockDownWall(unsigned int src,unsigned int dst);
    void fillBorders(unsigned int pos);
    
    int cellNPos(unsigned int pos){return (pos>=_width)?pos-_width:-1;}
    int cellEPos(unsigned int pos){return ((pos%_width)<_width-1)?pos+1:-1;}
    int cellSPos(unsigned int pos){return ((pos/_width)<_height-1)?pos+_width:-1;}
    int cellWPos(unsigned int pos){return ((pos%_width)>0)?pos-1:-1;}
    
    const unsigned int _width;
    const unsigned int _height;
    std::vector<Cell> _map;
};
#endif