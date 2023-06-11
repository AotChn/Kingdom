#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>


namespace resources{

class TM{
    
std::map<std::string, sf::Texture*> texture_map;
public:
sf::Texture *get_texture(std::string filepath){

    for (auto element: texture_map) {
        if (element.first == filepath)
            return element.second;
    }

    sf::Texture* texture = new sf::Texture();
    if(!texture->loadFromFile(filepath)){
        std::cout<<"texture failed to load";
    }

    texture_map[filepath] = texture;
    return texture_map[filepath];
    }


};

class FrameLoop{
    
int last;
int frames;
int size;
int m;
int rate;

public:

FrameLoop() : last(0), frames(0), size(0), m(0){}
FrameLoop(int f, int s) : last(0) , frames(f), size(s) {}

void set_params(int f, int s, int r){
    frames = f;
    size = s;
    rate = r;
}

int get_next(){

    if(m == rate){
        if(last == frames-1)
            last = 0;
        else if(last == 0)
            last = 1;
        else
            last++;
        m = 0;
    }
    else
        m++;
    return last*size;
}

};


}

#endif 


//1 2 3 4 5 6 
//1 2 3 4 5 6 7 8 9 10 11 12 

