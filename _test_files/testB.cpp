#include "gtest/gtest.h"
#include <iostream>
#include "../src/graphics/animate.h"
#include "../src/graphics/board/new_board.h"


TEST(OBSERVER, simple){
    sf::RenderWindow w;
    Window_Subject sub;
    Window_Observer o1, o2, o3, o4 ,o5;

    sub.Attach(&o1);
    sub.Attach(&o2);
    sub.Attach(&o3);

    sub.Detach(&o2);
    sub.Attach(&o4);
    sub.Attach(&o5);

    sub.Notify(w,0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running basic_test.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}