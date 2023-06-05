#pragma once

#include "command.h"
#include "../observer/Cmd_Oberver.h"
#include "../object/unit/unit.h"


struct MoveUnitCommandPackage{
  Unit* _unit;
  int _x, _y,
  _xBefore, _yBefore;
};

class MoveUnitCommand : public Command, Cmd_Subject
{
public:
  MoveUnitCommand(Unit* unit, int x, int y)
  { 
    _package._unit = unit;
    _package._x = x;
    _package._y = y;
    _package._xBefore = -1;
    _package._yBefore = -1;
  }

  virtual ~MoveUnitCommand(){}

  virtual void execute()
  {
    _package._xBefore = _package._unit->get_x();
    _package._yBefore = _package._unit->get_y();
    _package._unit->moveTo(_package._x, _package._y);
    Notify(this, Command::cmd_type::MoveUnit);
  }
  
  virtual void undo(){
    _package._unit->moveTo(_package._xBefore,_package._yBefore);
  }

  MoveUnitCommandPackage& getPackage(){ return _package;}

private:
  MoveUnitCommandPackage _package;
};
