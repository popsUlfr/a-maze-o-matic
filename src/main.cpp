#include "termbox.hpp"
#include "mazegame.hpp"

#include <iostream>

int main(){
    Termbox tb;
    MazeGame(tb).run();
    return 0;
}