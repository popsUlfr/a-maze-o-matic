#ifndef _TERMBOX_HPP
#define _TERMBOX_HPP

#include <stdexcept>
#include <string>

class Termbox{
public:
    explicit Termbox();
    virtual ~Termbox();
    void run();
private:
    void drawScreen();
    void drawRectangle(int tlx,int tly,int brx,int bry,uint16_t color);
    void drawMaze(int tlx,int tly,int brx,int bry,uint16_t color);
};

class TermboxInitException: public std::runtime_error{
public:
    explicit TermboxInitException(int code);
    static std::string errorStringPrinter(int code);
    int getErrorCode(){return _code;}
private:
    int _code;
};
#endif