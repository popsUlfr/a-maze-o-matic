#ifndef _AI_HPP
#define _AI_HPP

class MazePlayground;
class Actor;

class AI{
public:
    AI(){}
    virtual ~AI(){}
    
    virtual void run(const MazePlayground* mp,Actor* actor)=0;
    virtual void stop()=0;
};
#endif