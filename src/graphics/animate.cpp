#include "animate.h"

animate::animate(){
    window.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"KINGDOM");
    window.setFramerateLimit(60);
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

    Notify(window, Draw);
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

        default:
        break;
        }
    }
    Notify(window, event.type);
}


