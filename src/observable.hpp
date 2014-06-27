#ifndef _OBSERVABLE_HPP
#define _OBSERVABLE_HPP

#include "observer.hpp"

template<class T>
class Observable{
public:
    Observable():_observer(nullptr){}
    virtual ~Observable(){}
    
    virtual void attachObserver(Observer<T>* observer){
        _observer=observer;
    }
    
    virtual void notifyObserver(T& o){
        if(_observer!=nullptr)
            _observer->update(o);
    }
protected:
    Observer<T> *_observer;
};
#endif