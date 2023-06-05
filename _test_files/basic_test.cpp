#include "gtest/gtest.h"
#include <iostream>
#include "../src/graphics/animate.h"
#include "../src/graphics/board/new_board.h"


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running basic_test.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}