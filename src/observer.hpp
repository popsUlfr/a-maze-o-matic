#ifndef _OBSERVER_HPP
#define _OBSERVER_HPP

template<class T>
class Observer{
public:
    Observer(){}
    virtual ~Observer(){}
    
    virtual void update(T&)=0;
};
#endif