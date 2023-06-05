#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "iObserver.h"
#include "../command/command.h"


class Cmd_Observer : public iObserver
{
public:
  virtual ~Cmd_Observer(){}
  
  virtual void onNotify(Command* cmd, Command::cmd_type type) = 0;

};

class Cmd_Subject : public iSubject 
{
public:
  virtual ~Cmd_Subject(){
  }

  //Notify all the observer that this command "cmd" executed and type = command::command_type::(what type it is)
  //The idea is to static cast "cmd" to corresponding command object and 
  //call get_package() to recieve all the info stored inside the cmd 
  virtual void Notify(Command* cmd, Command::cmd_type type){
    if(_sub_debug)
      How_many_observer();
    auto w = _head;
    while(w !=nullptr){
      auto d = w->_data;
      static_cast<Cmd_Observer*>(d)->onNotify(cmd, type);
      w = w->_next;
    }

  }
};
