#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "iObserver.h"
#include 

struct unit_info{
    int command,
        _x, _y,
        _xBefore, _yBefore;
}
class Unit_Observer : public iObserver
{
public:
  virtual ~Unit_Observer(){}
  
  virtual void onNotify(unit_info package) = 0;

};

class Unit_Subject : public iSubject 
{
public:
  virtual ~Unit_Subject(){
  }
  virtual void Notify(unit_info package){
    if(_debug)
      How_many_observer();
    auto w = _head;
    while(w !=nullptr){
      auto d = w->_data;
      static_cast<Unit_Observer*>(d)->onNotify(package);
      w = w->_next;
    }

  }
};
