#pragma once

#include "command.h"
#include "../object/entity/unit.h"
#include "../object/grids.h"




class MoveUnitCommand : public Command
{
public:
  MoveUnitCommand(Unit* unit, Grid* grid, int x, int y)
  { 
    _grid = grid;
    _unit = unit;
    _x = x;
    _y = y;
    _xBefore = _unit->get_x();
    _yBefore = _unit->get_y();
  }

  virtual ~MoveUnitCommand(){}

  //Update the position of Unit to _x, _y AND Notify the obeserver
  virtual void execute()
  {

    _grid->detachUnit(_unit->get_cord()); //detach unit from the grid
    _unit->moveTo(_x, _y);
    _unit->setMove();
    _grid->attachUnit(_unit);
  }
  
  //Undo the position of Unit AND Notify the obeserver
  virtual void undo(){
    _grid->detachUnit(_unit->get_cord());
    _unit->moveTo(_xBefore,_yBefore);
    _unit->unsetMove();
    _grid->attachUnit(_unit);
  }


// private:
  Unit* _unit;
  Grid* _grid;
  int _x, _y,
  _xBefore, _yBefore;
};
