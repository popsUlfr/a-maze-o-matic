# A-MAZE-O-MATIC
## Introduction
A little game that I programmed in C++11 using the lean and clean [ncurses](https://en.wikipedia.org/wiki/Ncurses) alternative:
[Termbox](https://github.com/nsf/termbox)

![It's a-MAZE-ing!](https://github.com/popsulfr/a-maze-o-matic/raw/master/res/snapshot1.png)

Right now Depth-First Search is implemented for generating the maze and for the AI to find an exit path.

## How to build?
If you installed termbox to /usr/local you can just do
```
make
```
Header and library locations can be supplied directly to make e.g.:
```
make HEADERFLAGS=-I/home/popsulfr/work/termbox-out/include LIBFLAGS=-L/home/popsulfr/work/termbox-out/lib
```
To build a statically linked `amazeomatic_static` (only termbox and libstdc++)
```
make amazeomatic_static
```
To clean
```
make clean
```

## How to play?
The goal is to race the ai opponent using the arrow keys in order to be the first one to reach the opposite exit.
The *ESCAPE* key quits the game while the *SPACE* key creates a new maze discarding the current one.

## TODO
* Clean up the main *MazeGame* class (and some other stuff too...)
* Pause Button
* Custom color mappings/symbol mappings
* Animated Transitions?
* ...

## Thanks
A Big thank you to [nsf](https://github.com/nsf) for creating Termbox! You rock! :D