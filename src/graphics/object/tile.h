#pragma once


#include "type_def.h"
#include "onBoard.h"


class Tile : public onBoard
{
private:
    /* data */
    sf::Color _color[2];
public:
    Tile(cord_t where = cord_t()) : onBoard(where){}
    /*****************************************************
     * VIRTUAL 
     */
    
    virtual void draw(sf::RenderWindow& window) override{
        int w = 15;
        int& dx = onBoard::DX, &dy = onBoard::DY;
        int i = get_cord().first, j = get_cord().second;
        sf::RectangleShape s;
        s.setFillColor(_color[1]); 

        //Outline
        {
            s.setPosition(sf::Vector2f((dx*i)-(dx/w),dy*j));
            s.setSize(sf::Vector2f((dx/w), dy));
            window.draw(s);
            s.setPosition(sf::Vector2f((dx*(i+1)),dy*j));
            window.draw(s);
            s.setPosition(sf::Vector2f((dx*i),(dy*j)-(dy/w)));
            s.setSize(sf::Vector2f((dx), dy/w));
            window.draw(s);
            s.setPosition(sf::Vector2f((dx*i),dy*(j+1)));
            s.setSize(sf::Vector2f((dx), dy/w));
            window.draw(s);
        }

        //Fill
        {
            
            s.setFillColor(_color[0]); 
            s.setPosition(sf::Vector2f(dx*i,dy*j));
            s.setSize(sf::Vector2f(dx, dy));
            window.draw(s);
        }

        //Fill
    }
    /*****************************************************
     * MUTATOR 
     */
    void setFillColor(sf::Color c){
        _color[0] = c;
    }
    void setOutLineColor(sf::Color c){
        _color[1] = c;
    }
};
