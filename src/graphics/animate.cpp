#include "animate.h"

animate::animate(){
    window.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"KINGDOM");
    window.setFramerateLimit(60);
    b.set_param(10,10);
}

void animate::run(){
    while(window.isOpen()){
        process_events();
        update();
        render();
    }
}

 void animate::render(){
    window.clear(sf::Color(20, 20, 20,255));
    draw();
    window.display();
}

void animate::draw(){
    b.draw(window);

}

void animate::update(){
}

void animate::process_events(){
    sf::Event event;
    while(window.pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed:
            window.close();
            break;
            case sf::Event::MouseButtonPressed:{
            b.update();
            b.add(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            }
            break;

        }

    }
}


