#include "gtest/gtest.h"
#include <iostream>
#include "../src/graphics/animate.h"
#include "../src/graphics/board/new_board.h"
#include "../src/graphics/command/unit_command.h"

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

TEST(UOBSERVER, simple){
  Grid grid(10,10);
  Infantry i1(cord_t(0,0));
  MoveUnitCommand cmd(&i1, 1, 1);
  tile_info& t00 = grid[grid.find_tile(cord_t(0,0))];
  tile_info& t11 = grid[grid.find_tile(cord_t(1,1))];

  grid.emplaceUnit(&i1);

  cmd.execute();


  EXPECT_EQ(1, i1.get_x());
  EXPECT_EQ(1, i1.get_y());


  EXPECT_EQ(nullptr, t00.u);
  EXPECT_EQ(true, t00.empty);

  EXPECT_EQ(&i1, t11.u);
  EXPECT_EQ(false, t11.empty);

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running basic_test.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}