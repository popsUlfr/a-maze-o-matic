/*
 * Copyright (c) 2014 Philipp Richter
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
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

void Termbox::printString(int tlx,
                          int tly,
                          const std::string& string,
                          uint16_t color,
                          uint16_t bg)
{
    for(auto it:string){
        uint32_t c;
        tb_utf8_char_to_unicode(&c,&it);
        change_cell(tlx++,tly,c,color,bg);
    }
}

