#include "mazeplayground.hpp"

#include <random>

void MazePlayground::posRandomizer(){
    std::random_device rd;
    std::default_random_engine re(rd());
    std::uniform_int_distribution<unsigned int> uniDistEdge(0,3);
    unsigned int edge=uniDistEdge(rd);
    if((edge%2)==0){
        std::uniform_int_distribution<unsigned int> uniDistWidth(0,_maze.getWidth()-1);
        _currPos=_prevPos=_start=_maze.coordToPos(uniDistWidth(rd),(edge==0)?0:_maze.getHeight()-1);
        _end=_maze.coordToPos(uniDistWidth(rd),(edge==0)?_maze.getHeight()-1:0);
    }
    else{
        std::uniform_int_distribution<unsigned int> uniDistHeight(0,_maze.getHeight()-1);
        _currPos=_prevPos=_start=_maze.coordToPos((edge==1)?0:_maze.getWidth()-1,uniDistHeight(rd));
        _end=_maze.coordToPos((edge==1)?_maze.getWidth()-1:0,uniDistHeight(rd));
    }
}
