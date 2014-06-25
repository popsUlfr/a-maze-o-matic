#include "termbox.hpp"
#include "maze.hpp"
#include "mazeplayground.hpp"

#include <termbox.h>

#include <iostream>

std::string TermboxInitException::errorStringCreator(int code){
    std::string s;
    s+="ERROR ("+std::to_string(code)+") : ";
    switch(code){
        case TB_EUNSUPPORTED_TERMINAL:
            s+="Unsupported terminal!";
            break;
        case TB_EFAILED_TO_OPEN_TTY:
            s+="Failed to open TTY!";
            break;
        case TB_EPIPE_TRAP_ERROR:
            s+="Pipe Trap!";
            break;
        default:
            s+="Unknown";
    }
    return s;
}

TermboxInitException::TermboxInitException(int code):
runtime_error(TermboxInitException::errorStringCreator(code)),
_code(code){}


Termbox::Termbox(){
    int ret;
    if((ret=tb_init())<0) throw TermboxInitException(ret);
}

Termbox::~Termbox(){
    tb_shutdown();
}

void Termbox::drawMazeCell(Maze &maze,int tlx,int tly,unsigned int x,unsigned int y,uint16_t color){
    // First we place the walls North, East, South, West
    Maze::Cell c=maze.getCellAt(x,y);
    if(y==0 && (maze.hasWallN(c) || maze.hasBorderN(c))){
        tb_change_cell(tlx+(x<<2)+1,tly+(y<<1),0x2501,color,TB_DEFAULT);
        tb_change_cell(tlx+(x<<2)+2,tly+(y<<1),0x2501,color,TB_DEFAULT);
        tb_change_cell(tlx+(x<<2)+3,tly+(y<<1),0x2501,color,TB_DEFAULT);
    }
    if(maze.hasWallE(c) || maze.hasBorderE(c))
        tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+1,0x2503,color,TB_DEFAULT);
    if(maze.hasWallS(c) || maze.hasBorderS(c)){
        tb_change_cell(tlx+(x<<2)+1,tly+(y<<1)+2,0x2501,color,TB_DEFAULT);
        tb_change_cell(tlx+(x<<2)+2,tly+(y<<1)+2,0x2501,color,TB_DEFAULT);
        tb_change_cell(tlx+(x<<2)+3,tly+(y<<1)+2,0x2501,color,TB_DEFAULT);
    }
    if(x==0 && (maze.hasWallW(c) || maze.hasBorderW(c)))
        tb_change_cell(tlx+(x<<2),tly+(y<<1)+1,0x2503,color,TB_DEFAULT);
}

typedef enum{
    JUNC_NONE=0,
    JUNC_HORZ,
    JUNC_HORZ_RIGHT,
    JUNC_HORZ_LEFT,
    JUNC_VERT,
    JUNC_VERT_UP,
    JUNC_VERT_DOWN,
    JUNC_UP_LEFT,
    JUNC_UP_RIGHT,
    JUNC_UP_HORZ,
    JUNC_DOWN_LEFT,
    JUNC_DOWN_RIGHT,
    JUNC_DOWN_HORZ,
    JUNC_VERT_LEFT,
    JUNC_VERT_RIGHT,
    JUNC_VERT_HORZ
}Junction;

const uint32_t JunctionSymbols[]={
    0x0,    // JUNC_NONE
    0x2501, // JUNC_HORZ
    0x2501, // JUNC_HORZ_RIGHT
    0x2501, // JUNC_HORZ_LEFT
    0x2503, // JUNC_VERT
    0x2503, // JUNC_VERT_UP
    0x2503, // JUNC_VERT_DOWN
    0x251B, // JUNC_UP_LEFT
    0x2517, // JUNC_UP_RIGHT
    0x253B, // JUNC_UP_HORZ
    0x2513, // JUNC_DOWN_LEFT
    0x250F, // JUNC_DOWN_RIGHT
    0x2533, // JUNC_DOWN_HORZ
    0x252B, // JUNC_VERT_LEFT
    0x2523, // JUNC_VERT_RIGHT
    0x254B, // JUNC_VERT_HORZ
};

typedef enum{
    WALL_NORTH,
    WALL_EAST,
    WALL_SOUTH,
    WALL_WEST
}Wall;

const uint32_t WallSymbols[]={
    0x2501, // WALL_NORTH
    0x2503, // WALL_EAST
    0x2501, // WALL_SOUTH
    0x2503  // WALL_WEST
};

typedef enum{
    BORDER_NORTH_WEST,
    BORDER_NORTH,
    BORDER_NORTH_EAST,
    BORDER_EAST,
    BORDER_SOUTH_EAST,
    BORDER_SOUTH,
    BORDER_SOUTH_WEST,
    BORDER_WEST
}Border;

const uint32_t BorderSymbols[]={
    0x2501, // BORDER_NORTH
    0x2513, // BORDER_NORTH_EAST
    0x2503, // BORDER_EAST
    0x251B, // BORDER_SOUTH_EAST
    0x2501, // BORDER_SOUTH
    0x2517, // BORDER_SOUTH_WEST
    0x2503, // BORDER_WEST
    0x250F  // BORDER_NORTH_WEST
};

void Termbox::drawMazeFrame(Maze &maze,int tlx,int tly,unsigned int x,unsigned int y,uint16_t color){
    // Now we place the beautiful junction points for the corner cases
    Maze::Cell c=maze.getCellAt(x,y);
    if(y==0){ // The upper row of wall elements
        if(x==0){
            tb_change_cell(tlx,tly,0x250F,color,TB_DEFAULT);
            if(maze.hasWallE(c) || maze.hasBorderE(c))
                tb_change_cell(tlx+4,tly,0x2533,color,TB_DEFAULT);
            else
                tb_change_cell(tlx+4,tly,0x2501,color,TB_DEFAULT);
            if(maze.hasWallS(c) || maze.hasBorderS(c))
                tb_change_cell(tlx,tly+2,0x2523,color,TB_DEFAULT);
            else
                tb_change_cell(tlx,tly+2,0x2503,color,TB_DEFAULT);
        }
        else if(x==maze.getWidth()-1){
            tb_change_cell(tlx+(x<<2)+4,tly,0x2513,color,TB_DEFAULT);
            if(maze.hasWallS(c) || maze.hasBorderS(c))
                tb_change_cell(tlx+(x<<2)+4,tly+2,0x252B,color,TB_DEFAULT);
            else
                tb_change_cell(tlx+(x<<2)+4,tly+2,0x2503,color,TB_DEFAULT);
        }
        else if(maze.hasWallE(c) || maze.hasBorderE(c))
            tb_change_cell(tlx+(x<<2)+4,tly,0x2533,color,TB_DEFAULT);
        else
            tb_change_cell(tlx+(x<<2)+4,tly,0x2501,color,TB_DEFAULT);
    }
    else if(y==maze.getHeight()-1){
        if(x==0){
            tb_change_cell(tlx,tly+(y<<1)+2,0x2517,color,TB_DEFAULT);
            if(maze.hasWallE(c) || maze.hasBorderE(c))
                tb_change_cell(tlx+4,tly+(y<<1)+2,0x253B,color,TB_DEFAULT);
            else
                tb_change_cell(tlx+4,tly+(y<<1)+2,0x2501,color,TB_DEFAULT);
        }
        else if(x==maze.getWidth()-1)
            tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x251B,color,TB_DEFAULT);
        else if(maze.hasWallE(c) || maze.hasBorderE(c))
            tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x253B,color,TB_DEFAULT);
        else
            tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x2501,color,TB_DEFAULT);
    }
    else if(x==0){
        if(maze.hasWallS(c) || maze.hasBorderS(c))
            tb_change_cell(tlx,tly+(y<<1)+2,0x2523,color,TB_DEFAULT);
        else
            tb_change_cell(tlx,tly+(y<<1)+2,0x2503,color,TB_DEFAULT);
    }
    else if(x==maze.getWidth()-1){
        if(maze.hasWallS(c) || maze.hasBorderS(c))
            tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x252B,color,TB_DEFAULT);
        else
            tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x2503,color,TB_DEFAULT);
    }
}

void Termbox::drawPrettyJunctions(Maze &maze,int tlx, int tly, unsigned int x, unsigned int y, uint16_t color){
    Maze::Cell c=maze.getCellAt(x,y);
    Junction cd=JUNC_NONE;
    int pos;
    if(maze.hasWallS(c) || maze.hasBorderS(c))
        cd=JUNC_HORZ_LEFT;
    if(maze.hasWallE(c) || maze.hasBorderE(c)){
        if(cd==JUNC_HORZ_LEFT)
            cd=JUNC_UP_LEFT;
        else
            cd=JUNC_VERT_DOWN;
    }
    if((pos=maze.cellEPos((y*maze.getWidth())+x))>0){
        if(maze.hasWallS(maze.getCellByPos(pos)) || maze.hasBorderS(maze.getCellByPos(pos))){
            if(cd==JUNC_UP_LEFT)
                cd=JUNC_UP_HORZ;
            else if(cd==JUNC_VERT_DOWN)
                cd=JUNC_UP_RIGHT;
            else if(cd==JUNC_HORZ_LEFT)
                cd=JUNC_HORZ;
            else
                cd=JUNC_HORZ_RIGHT;
        }
    }
    else
        cd=JUNC_NONE;
    if((pos=maze.cellSPos((y*maze.getWidth())+x))>0){
        if(maze.hasWallE(maze.getCellByPos(pos)) || maze.hasBorderE(maze.getCellByPos(pos))){
            if(cd==JUNC_UP_HORZ)
                cd=JUNC_VERT_HORZ;
            else if(cd==JUNC_UP_LEFT)
                cd=JUNC_VERT_LEFT;
            else if(cd==JUNC_UP_RIGHT)
                cd=JUNC_VERT_RIGHT;
            else if(cd==JUNC_HORZ_LEFT)
                cd=JUNC_DOWN_LEFT;
            else if(cd==JUNC_HORZ_RIGHT)
                cd=JUNC_DOWN_RIGHT;
            else if(cd==JUNC_HORZ)
                cd=JUNC_DOWN_HORZ;
            else
                cd=JUNC_VERT_UP;
        }
    }
    else
        cd=JUNC_NONE;
    
    switch(cd){
        case JUNC_HORZ:
        case JUNC_HORZ_RIGHT:
        case JUNC_HORZ_LEFT:
            tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x2501,color,TB_DEFAULT);
            break;
        case JUNC_VERT:
        case JUNC_VERT_UP:
        case JUNC_VERT_DOWN:
            tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x2503,color,TB_DEFAULT);
            break;
        case JUNC_UP_LEFT:
            tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x251B,color,TB_DEFAULT);
            break;
        case JUNC_UP_RIGHT:
            tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x2517,color,TB_DEFAULT);
            break;
        case JUNC_UP_HORZ:
            tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x253B,color,TB_DEFAULT);
            break;
        case JUNC_DOWN_LEFT:
            tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x2513,color,TB_DEFAULT);
            break;
        case JUNC_DOWN_RIGHT:
            tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x250F,color,TB_DEFAULT);
            break;
        case JUNC_DOWN_HORZ:
            tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x2533,color,TB_DEFAULT);
            break;
        case JUNC_VERT_LEFT:
            tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x252B,color,TB_DEFAULT);
            break;
        case JUNC_VERT_RIGHT:
            tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x2523,color,TB_DEFAULT);
            break;
        case JUNC_VERT_HORZ:
            tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x254B,color,TB_DEFAULT);
            break;
        default: ;
    }
}

void Termbox::drawMazeDoor(Maze& maze, int tlx, int tly, unsigned int x, unsigned int y, uint32_t mazeDoorSymbol, uint16_t color,uint16_t bg){
    if(x==0)
        tb_change_cell(tlx,tly+(y<<1)+1,mazeDoorSymbol,color,bg);
    else if(x==maze.getWidth()-1)
        tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+1,mazeDoorSymbol,color,bg);
    else if(y==0){
        tb_change_cell(tlx+(x<<2)+1,tly,0,TB_DEFAULT,bg);
        tb_change_cell(tlx+(x<<2)+2,tly,mazeDoorSymbol,color,bg);
        tb_change_cell(tlx+(x<<2)+3,tly,0,TB_DEFAULT,bg);
    }
    else if(y==maze.getHeight()-1){
        tb_change_cell(tlx+(x<<2)+1,tly+(y<<1)+2,0,TB_DEFAULT,bg);
        tb_change_cell(tlx+(x<<2)+2,tly+(y<<1)+2,mazeDoorSymbol,color,bg);
        tb_change_cell(tlx+(x<<2)+3,tly+(y<<1)+2,0,TB_DEFAULT,bg);
    }
}


void Termbox::drawMaze(int tlx, int tly, int brx, int bry, uint16_t color){
    Maze maze((unsigned int)((brx-tlx)>>2),(unsigned int)((bry-tly)>>1)); // we shift twice the width to account for 2 more -
    MazePlayground mp(maze);
    
    for(unsigned int y=0;y<maze.getHeight();++y){
        for(unsigned int x=0;x<maze.getWidth();++x){
            
            // First we place the walls North, East, South, West
            drawMazeCell(maze,tlx,tly,x,y,color);
            
            drawMazeFrame(maze,tlx,tly,x,y,color);
            
            drawPrettyJunctions(maze,tlx,tly,x,y,color);
        }
    }
    drawMazeDoor(maze,tlx,tly,maze.posToCoordX(mp.getPosStart()),maze.posToCoordY(mp.getPosStart()),0x26A1,TB_BLACK,TB_RED);
    drawMazeDoor(maze,tlx,tly,maze.posToCoordX(mp.getPosEnd()),maze.posToCoordY(mp.getPosEnd()),0x2691,TB_BLACK,TB_GREEN);
}


void Termbox::drawScreen(){
    static const int margin=4;
    static const int minimalsize=8;
    tb_clear(); // We clear the whole screen
    tb_select_output_mode(TB_OUTPUT_NORMAL); // 8 colors mode
    int width=tb_width();
    int height=tb_height();
    if((width-((margin<<1)+minimalsize))>0 &&
        (height-((margin<<1)+minimalsize))>0
    ){
        drawMaze(margin,margin,width-margin,height-margin,TB_CYAN);
    }
    tb_present();
}

void Termbox::drawRectangle(int tlx,int tly,int brx,int bry, uint16_t color){
    if(tlx<brx && tly<bry){
        for(int x=tlx;x<brx;++x){
            for(int y=tly;y<bry;++y){
                tb_change_cell(x,y,0,TB_DEFAULT,color);
            }
        }
    }
}

void Termbox::run(){
    drawScreen();
    struct tb_event ev;
    bool cont=true;
    for(;cont;){
        int type=tb_poll_event(&ev);
        switch(type){
            case TB_EVENT_KEY:
                if(ev.key==TB_KEY_ESC)
                    cont=false;
                else if(ev.key==TB_KEY_SPACE)
                    drawScreen();
                break;
            case TB_EVENT_RESIZE:
                drawScreen();
                break;
            default:
                std::cerr << "Unkown Event type " << type << std::endl;
        }
    }
}



