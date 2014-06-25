#ifndef _TERMBOX_HPP
#define _TERMBOX_HPP

#include <termbox.h>

#include <stdexcept>
#include <string>

class Termbox{
public:
    explicit Termbox();
    virtual ~Termbox();
    
    int width() const{return tb_width();}
    int height() const{return tb_height();}
    
    /**
     * See termbox.h for color codes
     */
    void change_cell(int x,int y,uint32_t ch, uint16_t fg, uint16_t bg) const{tb_change_cell(x,y,ch,fg,bg);}
    
    void clear() const{tb_clear();}
    
    void present() const{tb_present();}
    
    int peek_event(struct tb_event *event, int timeout){
        return tb_peek_event(event,timeout);
    }
    int poll_event(struct tb_event *event){
        return tb_poll_event(event);
    }
};

class TermboxInitException: public std::runtime_error{
public:
    explicit TermboxInitException(int code):
    runtime_error(TermboxInitException::errorStringCreator(code)),
    _code(code){}
    static std::string errorStringCreator(int code);
    int getErrorCode(){return _code;}
private:
    int _code;
};
#endif