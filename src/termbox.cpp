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


Termbox::Termbox(){
    int ret;
    if((ret=tb_init())<0) throw TermboxInitException(ret);
}

Termbox::~Termbox(){
    tb_shutdown();
}

void Termbox::drawMaze(int tlx, int tly, int brx, int bry, uint16_t color){
    int width=brx-tlx;
    int height=bry-tly;
    Maze m((unsigned int)(width>>1),(unsigned int)(height>>1));
    for(int y=tly+1;y<bry;y+=2){
        for(int x=tlx+1;x<brx;x+=2){
            Maze::Cell& c=m.getCellAt((x==width-1)?(x-1)>>1:x>>1,(y==height-1)?(y-1)>>1:y>>1);
            if(m.hasWallN(c) || m.hasBorderN(c))
                tb_change_cell(x,y-1,0,TB_DEFAULT,color);
            if(m.hasWallE(c) || m.hasBorderE(c))
                tb_change_cell(x+1,y,0,TB_DEFAULT,color);
            if(m.hasWallS(c) || m.hasBorderS(c))
                tb_change_cell(x,y-1,0,TB_DEFAULT,color);
            if(m.hasWallW(c) || m.hasBorderW(c))
                tb_change_cell(x-1,y,0,TB_DEFAULT,color);
        }
    }
}


void Termbox::drawScreen(){
    static const int margin=4;
    tb_clear(); // We clear the whole screen
    tb_select_output_mode(TB_OUTPUT_NORMAL); // 8 colors mode
    int width=tb_width();
    int height=tb_height();
    if(width>16 && height>16){
        drawMaze(0,0,40,40,TB_CYAN);
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



