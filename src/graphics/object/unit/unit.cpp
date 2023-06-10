#include "unit.h"


/*****************************************************
 * BIG3
 */

    Unit::Unit(){}
    Unit::Unit(cord_t cord, cost_t mCost): _mCost(mCost){
        set_cord(cord);
    }

/*****************************************************
 * VIRTUAL 
 */
    void Unit::draw(sf::RenderWindow& window){
        window.draw(unit(sf::Color::Red));
    }

    sf::RectangleShape Unit::unit(sf::Color c){
        int u = DX * 1/4;
        sf::RectangleShape s;
        s.setFillColor(c); 
        s.setPosition(sf::Vector2f( DX * get_cord().first + u, DY * get_cord().second + u ) );
        s.setSize(sf::Vector2f(DX/2, DY/2));

        sf::Texture* T = texture.get_texture("textures/red_sample_unit.png");
        s.setTexture(T);


        return s;
    }


/*****************************************************
 * MUTATOR
 */



/*****************************************************
 * GETTER
 */
