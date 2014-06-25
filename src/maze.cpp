#include "maze.hpp"

#include <stack>
#include <random>
#include <iostream>

unsigned int Maze::fillNeighbours(unsigned int pos, unsigned int nbCells[4]) const{
    unsigned int cells=0;
    int tmp;
    if((tmp=cellNPos(pos))>=0 && ((_map.at(tmp) & MAZE_WALL_ALL)==MAZE_WALL_ALL))
        nbCells[cells++]=tmp;
    if((tmp=cellEPos(pos))>=0 && ((_map.at(tmp) & MAZE_WALL_ALL)==MAZE_WALL_ALL))
        nbCells[cells++]=tmp;
    if((tmp=cellSPos(pos))>=0 && ((_map.at(tmp) & MAZE_WALL_ALL)==MAZE_WALL_ALL))
        nbCells[cells++]=tmp;
    if((tmp=cellWPos(pos))>=0 && ((_map.at(tmp) & MAZE_WALL_ALL)==MAZE_WALL_ALL))
        nbCells[cells++]=tmp;
    return cells;
}

void Maze::knockDownWall(unsigned int src, unsigned int dst){
    if((unsigned int)cellNPos(src)==dst){
        _map.at(src)^=MAZE_WALL_NORTH;
        _map.at(dst)^=MAZE_WALL_SOUTH;
    }
    else if((unsigned int)cellEPos(src)==dst){
        _map.at(src)^=MAZE_WALL_EAST;
        _map.at(dst)^=MAZE_WALL_WEST;
    }
    else if((unsigned int)cellSPos(src)==dst){
        _map.at(src)^=MAZE_WALL_SOUTH;
        _map.at(dst)^=MAZE_WALL_NORTH;
    }
    else if((unsigned int)cellWPos(src)==dst){
        _map.at(src)^=MAZE_WALL_WEST;
        _map.at(dst)^=MAZE_WALL_EAST;
    }
}

void Maze::fillBorders(unsigned int pos){
    if(cellNPos(pos)<0)
        _map.at(pos)^=MAZE_BORDER_NORTH;
    if(cellWPos(pos)<0)
        _map.at(pos)^=MAZE_BORDER_WEST;
    if(cellEPos(pos)<0)
        _map.at(pos)^=MAZE_BORDER_EAST;
    if(cellSPos(pos)<0)
        _map.at(pos)^=MAZE_BORDER_SOUTH;
}

void Maze::depthFirstSearchAlgorithm(){
    std::random_device rd;
    std::default_random_engine re(rd());
    std::uniform_int_distribution<unsigned int> unintVector(0,_map.size()-1);
    unsigned int pos=unintVector(re);
    
    unsigned int totalCells=_map.size();
    unsigned int visitedCells=0;
    std::stack<unsigned int> vecPosStack;
    unsigned int nbCells[4];
    
    for(;visitedCells<totalCells-1;){
        fillBorders(pos);
        unsigned int cells;
        if((cells=fillNeighbours(pos,nbCells))>0){
            std::uniform_int_distribution<unsigned int> unintNb(0,cells-1);
            unsigned int newpos=nbCells[unintNb(re)];
            knockDownWall(pos,newpos);
            vecPosStack.push(pos);
            pos=newpos;
            ++visitedCells;
        }
        else{
            if(vecPosStack.empty()) break;
            pos=vecPosStack.top();
            vecPosStack.pop();
        }
    }
}

Maze::Maze(unsigned int width, unsigned int height):
_width(width),_height(height),
_map(width*height,MAZE_WALL_ALL)
{
    depthFirstSearchAlgorithm();
}

void Maze::printMaze(){
    unsigned int x;
    for(x=0;x<_width;++x){
        if(x==0)
            std::cout << MAZE_CORNER_SYMBOL;
        std::cout << MAZE_HORIZONTAL_WALL_SYMBOL;
        if(x==_width-1)
            std::cout << MAZE_CORNER_SYMBOL;
        else
            std::cout << MAZE_JUNCTION_SYMBOL;
    }
    std::cout << std::endl;
    for(unsigned y=0;y<_height;++y){
        for(x=0;x<_width;++x){
            if(x==0)
                std::cout << MAZE_VERTICAL_WALL_SYMBOL;
            std::cout << MAZE_CELL_SPACE;
            if(hasWallE(getCellAt(x,y)))
                std::cout << MAZE_VERTICAL_WALL_SYMBOL;
            else
                std::cout << MAZE_JUNCTION_SPACE;
        }
        std::cout << std::endl;
        for(x=0;x<_width;++x){
            if(x==0)
                std::cout << MAZE_JUNCTION_SYMBOL;
            Cell &c=getCellAt(x,y);
            if(hasWallS(c) || hasBorderS(c)){
                std::cout << MAZE_HORIZONTAL_WALL_SYMBOL;
            }
            else{
                std::cout << MAZE_CELL_SPACE;
            }
            int pos;
            if(hasWallS(c) || hasWallE(c) || hasBorderS(c) || hasBorderE(c) ||
                (((pos=cellEPos((y*_width)+x))>=0) && (hasWallS(_map.at(pos)) || hasBorderS(_map.at(pos))))
                || (((pos=cellSPos((y*_width)+x))>=0) && (hasWallE(_map.at(pos)) || hasBorderE(_map.at(pos))))
            ){
                std::cout << MAZE_JUNCTION_SYMBOL;
            }
            else
                std::cout << MAZE_JUNCTION_SPACE;
        }
        std::cout << std::endl;
    }
}

