#ifndef _OBSERVER_HPP
#define _OBSERVER_HPP
class Observer{
public:
    Observer(){}
    virtual ~Observer(){}
    
    virtual void update()=0;
};
#endif