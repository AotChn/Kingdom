#include <iostream>
// #include "src/graphics/animate.cpp"
// #include "src/data/binaryfiles.h"
// #include "src/network/socket.h"

// #include <SFML/Network.hpp>
// #include "network_sample/sample.h"
// #include <SFML/Graphics.hpp>

#include "src/graphics/animate.h"
#include "src/graphics/board/new_board.h"

using namespace std;

int main(int argc, char **argv){

    animate game;
    Board b(10,10);
    game.Attach(&b);
    game.run();

    deque<int> q;
    q.push_back(1);
    q.push_back(2);
    q.push_back(3);

    auto it = q.begin();


    std::cout << "End of Main\n";
}

