#ifndef _AI_HPP
#define _AI_HPP

#include <atomic>

class MazePlayground;
class Actor;

class AI{
public:
    AI():_running(false){}
    virtual ~AI(){}
    
    virtual void run(const MazePlayground* mp,Actor* actor)=0;
    virtual void stop()=0;
    
    virtual bool isRunning(){return _running.load();}
    
    virtual void resetAI()=0;
protected:
    std::atomic_bool _running;
};
#endif