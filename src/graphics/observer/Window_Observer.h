#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "iObserver.h"

class Window_Observer : public iObserver
{
public:
  virtual ~Window_Observer(){}
  
  virtual void onNotify(sf::RenderWindow& window, int event) {
    if(_obs_debug) std::printf("[WObserver%d] : onNotify!\n", _no);
  };

};

class Window_Subject : public iSubject 
{
public:
  virtual ~Window_Subject(){
  }
  virtual void Notify(sf::RenderWindow& window, int event){
    if(_sub_debug)
      How_many_observer();
    auto w = _head;
    while(w !=nullptr){
      auto d = w->_data;
      static_cast<Window_Observer*>(d)->onNotify(window, event);
      w = w->_next;
    }

  }

};



