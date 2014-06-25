#include "termbox.hpp"
#include "maze.hpp"

#include <iostream>

void termboxThread(){
    Termbox().run();
}

int main(){
    termboxThread();
    return 0;
}