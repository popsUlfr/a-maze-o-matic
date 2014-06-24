#include "maze.hpp"

#include <ctime>
#include <stack>
#include <random>
#include <iostream>

unsigned int Maze::fillNeighbours(unsigned int pos, unsigned int nbCells[4]){
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



Maze::Maze(unsigned int width, unsigned int height):
_width(width),_height(height),
_map(width*height,MAZE_WALL_ALL)
{
    std::random_device rd;
    std::default_random_engine re(rd());
    std::uniform_int_distribution<unsigned int> unintVector(0,_map.size()-1);
    unsigned int pos=unintVector(re);
    
    unsigned int totalCells=_map.size();
    std::cout << "Total Cells: " << totalCells << std::endl;
    unsigned int visitedCells=0;
    std::stack<unsigned int> vecPosStack;
    unsigned int nbCells[4];
    
    for(;visitedCells<totalCells-1;){
        //fillBorders(pos);
        
        printMaze();
        std::cout << "Current pos: " << pos << std::endl;
        unsigned int cells;
        if((cells=fillNeighbours(pos,nbCells))>0){
            std::uniform_int_distribution<unsigned int> unintNb(0,cells-1);
            unsigned int newpos=nbCells[unintNb(re)];
            knockDownWall(pos,newpos);
            std::cout << "Pushing " << pos << ", stacksize: "<< vecPosStack.size() << ", next: "<< newpos<< " Visited cells: " << visitedCells+1<< std::endl;
            vecPosStack.push(pos);
            pos=newpos;
            ++visitedCells;
        }
        else{
            if(vecPosStack.empty()) break;
            pos=vecPosStack.top();
            std::cout << "Popping " << pos << ", stacksize: " << vecPosStack.size() <<std::endl;
            vecPosStack.pop();
        }
    }
}

void Maze::printMazeNormal(){
    for(std::vector<Cell>::size_type i=0;i<_map.size();++i){
        std::cout << i
        << ((hasWallN(_map.at(i)))?"N":"")
        << ((hasWallE(_map.at(i)))?"E":"")
        << ((hasWallS(_map.at(i)))?"S":"")
        << ((hasWallW(_map.at(i)))?"W":"")
        << "|";
        if((i%_width)==_width-1) std::cout << std::endl;
    }
}

void Maze::printMaze(){
    printMazeNormal();
    unsigned int x;
    for(x=0;x<_width;++x){
        if(x==0)
            std::cout << "*";
        std::cout << "---";
        if(x==_width-1)
            std::cout << "*";
        else
            std::cout << "+";
    }
    std::cout << std::endl;
    for(unsigned y=0;y<_height;++y){
        for(x=0;x<_width;++x){
            if(x==0)
                std::cout << "|";
            std::cout << "   ";
            if(hasWallE(getCellAt(x,y)))
                std::cout << "|";
            else
                std::cout << " ";
        }
        std::cout << std::endl;
        for(x=0;x<_width;++x){
            if(x==0)
                std::cout << "+";
            Cell &c=getCellAt(x,y);
            if(hasWallS(c) || hasBorderS(c)){
                std::cout << "---";
            }
            else{
                std::cout << "   ";
            }
            int pos;
            if(hasWallS(c) || hasWallE(c) || hasBorderS(c) || hasBorderE(c) ||
                (((pos=cellEPos((y*_width)+x))>=0) && (hasWallS(_map.at(pos)) || hasBorderS(_map.at(pos))))
                || (((pos=cellSPos((y*_width)+x))>=0) && (hasWallE(_map.at(pos)) || hasBorderE(_map.at(pos))))
            ){
                std::cout << "+";
            }
            else
                std::cout << " ";
        }
        std::cout << std::endl;
    }
}

/*
void Maze::printMaze(){
    printMazeNormal();
    unsigned int maxX=(_width<<1)+1;
    unsigned int maxY=(_height<<1)+1;
    for(unsigned y=0;y<maxY;++y){
        for(unsigned x=0;x<maxX;++x){
            Cell& c=getCellAt((x==maxX-1)?(x-1)>>1:x>>1,(y==maxY-1)?(y-1)>>1:y>>1);
            if((x==0 || x==maxX-1) && (y==0 || y==maxY-1))
                std::cout << "*";
            else if((y%2)==0 && (x%2)==0 && 
                (((x==0) || (x==maxX-1) || (y==0) || (y==maxY-1)) ||
                (hasWallN(c) || hasWallE(c))))
                std::cout << "+";
            else if((y%2)==0 && (x%2)==1 &&
                ((y==0 || y==maxY-1) ||
                (hasWallN(c))))
                std::cout << "---";
            else if((y%2)==1 && (x%2)==0 &&
                (((x==0) || (x==maxX-1)) ||
                (hasWallE(c))))
                std::cout << "|";
            else if((x%2)==0)
                std::cout << " ";
            else
                std::cout << "   ";
        }
        std::cout << std::endl;
    }
}
*/
