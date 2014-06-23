#include "termbox.hpp"

#include <termbox.h>

#include <iostream>
#include <random>
#include <ctime>

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

void Termbox::drawScreen(){
    static const int margin=4;
    tb_clear(); // We clear the whole screen
    tb_select_output_mode(TB_OUTPUT_NORMAL); // 8 colors mode
    int width=tb_width();
    int height=tb_height();
    if((width-(margin<<1))>0 &&
        (height-(margin<<1))>0){
        drawRectangle(margin,margin,width-margin,height-margin,TB_CYAN);
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

void Termbox::generateMaze(){
    int width=tb_width();
    int height=tb_height();
    std::default_random_engine re(std::time(0));
    std::uniform_int_distribution<int> unintWidth(0,width);
    std::uniform_int_distribution<int> unintHeight(0,height);
    int x=unintWidth(re);
    int y=unintHeight(re);
    
    const int nbcells=8;
    struct tb_cell *ncells[nbcells];
    
    
    if(x>0 && y>0){ // North West
        tb_blit();
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



