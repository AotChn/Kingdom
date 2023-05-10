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
    window.clear(sf::Color(20, 20, 20,255));
    draw();
    window.display();
}

void animate::draw(){
    b.draw_grid(25,25,window);
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
        }

    }
}


