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
    window.clear(BACKGROUND_DARK);
    draw();
    window.display();
}

void animate::draw(){
    b.draw(window);
}

void animate::update(){
    b.update();
}

void animate::process_events(){

    sf::Event event;
    while(window.pollEvent(event)){
        switch(event.type){
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::MouseButtonPressed:{
                b.cursor_click(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                // b.update();
                // b.add(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                break;
            }
        case sf::Event::MouseButtonReleased:{
                b.cursor_release(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                break;
            }   
        case sf::Event::MouseMoved:{
                b.cursor_move(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                break;
            }

        default:{
                b.cursor_idle();
            }
        }
    }
}

