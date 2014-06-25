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

Termbox::Termbox(){
    int ret;
    if((ret=tb_init())<0) throw TermboxInitException(ret);
    tb_select_output_mode(TB_OUTPUT_NORMAL);
}

Termbox::~Termbox(){
    tb_shutdown();
}
