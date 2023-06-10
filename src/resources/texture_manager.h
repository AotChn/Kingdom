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
    //std::cout << element.first << " " << filePath << std::endl;

    // We also want to check that the path is not invalid, as otherwise it would just be
    // stuck as invalid, because it would technically have an entry in the map
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


}

#endif 