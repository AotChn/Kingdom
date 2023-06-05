#pragma once

#include "command.h"
#include "../object/unit/unit.h"

class MoveUnitCommand : public Command
{
public:
  MoveUnitCommand(Unit* unit, int x, int y)
  : _unit(unit),
    _x(x),
    _y(y)
  { _xBefore = -1; _yBefore = -1;}

  virtual void execute()
  {
    _xBefore = _unit->get_x();
    _yBefore = _unit->get_y();
    _unit->moveTo(_x, _y);
  }
  
  virtual void undo(){
    unit->moveTo(_xBefore,_yBefore);
  }
private:
  Unit* _unit;
  int _x, _y,
  _xBefore, _yBefore;

};
