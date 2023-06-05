#pragma once

#include "command.h"
#include "../observer/Cmd_Oberver.h"
#include "../object/unit/unit.h"


struct MoveUnitCommandPackage{
  Unit* _unit;
  int _x, _y,
  _xBefore, _yBefore;
};

class MoveUnitCommand : public Command, public Cmd_Subject
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

  //Update the position of Unit to _x, _y AND Notify the obeserver
  virtual void execute()
  {
    _package._xBefore = _package._unit->get_x();
    _package._yBefore = _package._unit->get_y();
    _package._unit->moveTo(_package._x, _package._y);
    Notify(this, Command::cmd_type::MoveUnit);
  }
  
  //Undo the position of Unit AND Notify the obeserver
  virtual void undo(){
    _package._unit->moveTo(_package._xBefore,_package._yBefore);
  }

  MoveUnitCommandPackage& getPackage(){ return _package;}

private:
  MoveUnitCommandPackage _package; //a Wrapper to hold all variables
};
