#include "termbox.hpp"
#include "maze.hpp"

#include <iostream>

int main(){
    //Termbox().run();
    Maze m(4,4);
    m.printMaze();
    return 0;
}