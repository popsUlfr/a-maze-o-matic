#include "termbox.hpp"
#include "maze.hpp"

#include <termbox.h>

#include <iostream>

std::string TermboxInitException::errorStringPrinter(int code){
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
runtime_error(TermboxInitException::errorStringPrinter(code)),
_code(code){}


Termbox::Termbox():_maze(nullptr){
    int ret;
    if((ret=tb_init())<0) throw TermboxInitException(ret);
}

Termbox::~Termbox(){
    delete(_maze);
    tb_shutdown();
}

typedef enum{
    DIR_NONE,
    DIR_HORZ,
    DIR_HORZ_RIGHT,
    DIR_HORZ_LEFT,
    DIR_VERT,
    DIR_VERT_UP,
    DIR_VERT_DOWN,
    DIR_LEFT_UP,
    DIR_RIGHT_UP,
    DIR_LEFT_UP_RIGHT,
    DIR_LEFT_DOWN,
    DIR_RIGHT_DOWN,
    DIR_LEFT_DOWN_RIGHT,
    DIR_UP_LEFT_DOWN,
    DIR_UP_RIGHT_DOWN,
    DIR_LEFT_UP_RIGHT_DOWN
}CornerDir;

void Termbox::drawMaze(int tlx, int tly, int brx, int bry, uint16_t color){
    delete(_maze); // we free the old maze
    _maze=new Maze((unsigned int)((brx-tlx)>>2),(unsigned int)((bry-tly)>>1)); // we shift twice the width to account for 2 more -
    for(unsigned int y=0;y<_maze->getHeight();++y){
        for(unsigned int x=0;x<_maze->getWidth();++x){
            
            // First we place the walls North, East, South, West
            Maze::Cell c=_maze->getCellAt(x,y);
            if(y==0 && (_maze->hasWallN(c) || _maze->hasBorderN(c))){
                tb_change_cell(tlx+(x<<2)+1,tly+(y<<1),0x2501,color,TB_DEFAULT);
                tb_change_cell(tlx+(x<<2)+2,tly+(y<<1),0x2501,color,TB_DEFAULT);
                tb_change_cell(tlx+(x<<2)+3,tly+(y<<1),0x2501,color,TB_DEFAULT);
            }
            if(_maze->hasWallE(c) || _maze->hasBorderE(c))
                tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+1,0x2503,color,TB_DEFAULT);
            if(_maze->hasWallS(c) || _maze->hasBorderS(c)){
                tb_change_cell(tlx+(x<<2)+1,tly+(y<<1)+2,0x2501,color,TB_DEFAULT);
                tb_change_cell(tlx+(x<<2)+2,tly+(y<<1)+2,0x2501,color,TB_DEFAULT);
                tb_change_cell(tlx+(x<<2)+3,tly+(y<<1)+2,0x2501,color,TB_DEFAULT);
            }
            if(x==0 && (_maze->hasWallW(c) || _maze->hasBorderW(c)))
                tb_change_cell(tlx+(x<<2),tly+(y<<1)+1,0x2503,color,TB_DEFAULT);
            
            // Now we place the beautiful junction points
            if(y==0){
                if(x==0){
                    tb_change_cell(tlx,tly,0x250F,color,TB_DEFAULT);
                    if(_maze->hasWallE(c) || _maze->hasBorderE(c))
                        tb_change_cell(tlx+4,tly,0x2533,color,TB_DEFAULT);
                    else
                        tb_change_cell(tlx+4,tly,0x2501,color,TB_DEFAULT);
                    if(_maze->hasWallS(c) || _maze->hasBorderS(c))
                        tb_change_cell(tlx,tly+2,0x2523,color,TB_DEFAULT);
                    else
                        tb_change_cell(tlx,tly+2,0x2503,color,TB_DEFAULT);
                }
                else if(x==_maze->getWidth()-1){
                    tb_change_cell(tlx+(x<<2)+4,tly,0x2513,color,TB_DEFAULT);
                    if(_maze->hasWallS(c) || _maze->hasBorderS(c))
                        tb_change_cell(tlx+(x<<2)+4,tly+2,0x252B,color,TB_DEFAULT);
                    else
                        tb_change_cell(tlx+(x<<2)+4,tly+2,0x2503,color,TB_DEFAULT);
                }
                else if(_maze->hasWallE(c) || _maze->hasBorderE(c))
                    tb_change_cell(tlx+(x<<2)+4,tly,0x2533,color,TB_DEFAULT);
                else
                    tb_change_cell(tlx+(x<<2)+4,tly,0x2501,color,TB_DEFAULT);
            }
            else if(y==_maze->getHeight()-1){
                if(x==0){
                    tb_change_cell(tlx,tly+(y<<1)+2,0x2517,color,TB_DEFAULT);
                    if(_maze->hasWallE(c) || _maze->hasBorderE(c))
                        tb_change_cell(tlx+4,tly+(y<<1)+2,0x253B,color,TB_DEFAULT);
                    else
                        tb_change_cell(tlx+4,tly+(y<<1)+2,0x2501,color,TB_DEFAULT);
                }
                else if(x==_maze->getWidth()-1)
                    tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x251B,color,TB_DEFAULT);
                else if(_maze->hasWallE(c) || _maze->hasBorderE(c))
                    tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x253B,color,TB_DEFAULT);
                else
                    tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x2501,color,TB_DEFAULT);
            }
            else if(x==0){
                if(_maze->hasWallS(c) || _maze->hasBorderS(c))
                    tb_change_cell(tlx,tly+(y<<1)+2,0x2523,color,TB_DEFAULT);
                else
                    tb_change_cell(tlx,tly+(y<<1)+2,0x2503,color,TB_DEFAULT);
            }
            else if(x==_maze->getWidth()-1){
                if(_maze->hasWallS(c) || _maze->hasBorderS(c))
                    tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x252B,color,TB_DEFAULT);
                else
                    tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x2503,color,TB_DEFAULT);
            }
            CornerDir cd=DIR_NONE;
            int pos;
            if(_maze->hasWallS(c) || _maze->hasBorderS(c))
                cd=DIR_HORZ_LEFT;
            if(_maze->hasWallE(c) || _maze->hasBorderE(c)){
                if(cd==DIR_HORZ_LEFT)
                    cd=DIR_LEFT_UP;
                else
                    cd=DIR_VERT_DOWN;
            }
            if((pos=_maze->cellEPos((y*_maze->getWidth())+x))>0){
                if(_maze->hasWallS(_maze->getCellByPos(pos)) || _maze->hasBorderS(_maze->getCellByPos(pos))){
                    if(cd==DIR_LEFT_UP)
                        cd=DIR_LEFT_UP_RIGHT;
                    else if(cd==DIR_VERT_DOWN)
                        cd=DIR_RIGHT_UP;
                    else if(cd==DIR_HORZ_LEFT)
                        cd=DIR_HORZ;
                    else
                        cd=DIR_HORZ_RIGHT;
                }
            }
            else
                cd=DIR_NONE;
            if((pos=_maze->cellSPos((y*_maze->getWidth())+x))>0){
                if(_maze->hasWallE(_maze->getCellByPos(pos)) || _maze->hasBorderE(_maze->getCellByPos(pos))){
                    if(cd==DIR_LEFT_UP_RIGHT)
                        cd=DIR_LEFT_UP_RIGHT_DOWN;
                    else if(cd==DIR_LEFT_UP)
                        cd=DIR_UP_LEFT_DOWN;
                    else if(cd==DIR_RIGHT_UP)
                        cd=DIR_UP_RIGHT_DOWN;
                    else if(cd==DIR_HORZ_LEFT)
                        cd=DIR_LEFT_DOWN;
                    else if(cd==DIR_HORZ_RIGHT)
                        cd=DIR_RIGHT_DOWN;
                    else if(cd==DIR_HORZ)
                        cd=DIR_LEFT_DOWN_RIGHT;
                    else
                        cd=DIR_VERT_UP;
                }
            }
            else
                cd=DIR_NONE;
            
            switch(cd){
                case DIR_HORZ:
                case DIR_HORZ_RIGHT:
                case DIR_HORZ_LEFT:
                    tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x2501,color,TB_DEFAULT);
                    break;
                case DIR_VERT:
                case DIR_VERT_UP:
                case DIR_VERT_DOWN:
                    tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x2503,color,TB_DEFAULT);
                    break;
                case DIR_LEFT_UP:
                    tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x251B,color,TB_DEFAULT);
                    break;
                case DIR_RIGHT_UP:
                    tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x2517,color,TB_DEFAULT);
                    break;
                case DIR_LEFT_UP_RIGHT:
                    tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x253B,color,TB_DEFAULT);
                    break;
                case DIR_LEFT_DOWN:
                    tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x2513,color,TB_DEFAULT);
                    break;
                case DIR_RIGHT_DOWN:
                    tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x250F,color,TB_DEFAULT);
                    break;
                case DIR_LEFT_DOWN_RIGHT:
                    tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x2533,color,TB_DEFAULT);
                    break;
                case DIR_UP_LEFT_DOWN:
                    tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x252B,color,TB_DEFAULT);
                    break;
                case DIR_UP_RIGHT_DOWN:
                    tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x2523,color,TB_DEFAULT);
                    break;
                case DIR_LEFT_UP_RIGHT_DOWN:
                    tb_change_cell(tlx+(x<<2)+4,tly+(y<<1)+2,0x254B,color,TB_DEFAULT);
                    break;
                default: ;
            }
        }
    }
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
                break;
            case TB_EVENT_RESIZE:
                drawScreen();
                break;
            default:
                std::cerr << "Unkown Event type " << type << std::endl;
        }
    }
}



