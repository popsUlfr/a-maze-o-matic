#ifndef _AI_HPP
#define _AI_HPP

#include "mazeplayground.hpp"

class AI{
public:
    AI(const MazePlayground &mp):_mp(mp){}
protected:
    const MazePlayground &_mp;
};
#endif