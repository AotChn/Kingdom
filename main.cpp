#include <iostream>
// #include "src/graphics/animate.cpp"
// #include "src/data/binaryfiles.h"
// #include "src/network/socket.h"

// #include <SFML/Network.hpp>
// #include "network_sample/sample.h"
// #include <SFML/Graphics.hpp>

#include "src/graphics/animate.h"
#include "src/graphics/board/board_copy.h"


int main(int argc, char **argv){

    animate game;
    board b;
    b.set_param(10,10);
    game.Attach(&b);
    game.run();
    game.Detach(&b);

    
    return 0;
}

