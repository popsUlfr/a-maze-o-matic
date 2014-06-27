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
#ifndef _TERMBOX_HPP
#define _TERMBOX_HPP

#include <termbox.h>

#include <stdexcept>
#include <string>

class Termbox{
public:
    explicit Termbox();
    virtual ~Termbox(){tb_shutdown();}
    
    virtual int width() const{return tb_width();}
    virtual int height() const{return tb_height();}
    
    /**
     * See termbox.h for color codes
     */
    virtual void change_cell(int x,int y,uint32_t ch, uint16_t fg, uint16_t bg) const{tb_change_cell(x,y,ch,fg,bg);}
    
    virtual void clear() const{tb_clear();}
    
    virtual void present() const{tb_present();}
    
    virtual int peek_event(struct tb_event *event, int timeout) const{
        return tb_peek_event(event,timeout);
    }
    virtual int poll_event(struct tb_event *event) const{
        return tb_poll_event(event);
    }
    
    virtual void printString(int tlx,int tly,const std::string& string,
        uint16_t color=TB_WHITE,uint16_t bg=TB_DEFAULT);
};

class TermboxInitException: public std::runtime_error{
public:
    explicit TermboxInitException(int code):
    runtime_error(TermboxInitException::errorStringCreator(code)),
    _code(code){}
    static std::string errorStringCreator(int code);
    virtual int getErrorCode(){return _code;}
private:
    int _code;
};
#endif