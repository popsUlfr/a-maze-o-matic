#ifndef _OBSERVABLE_HPP
#define _OBSERVABLE_HPP

#include "observer.hpp"

class Observable{
public:
    Observable():_observer(nullptr){}
    virtual ~Observable(){}
    
    virtual void attachObserver(Observer* observer){
        _observer=observer;
    }
    
    virtual void notifyObserver(){
        if(_observer!=nullptr)
            _observer->update();
    }
protected:
    Observer *_observer;
};
#endif