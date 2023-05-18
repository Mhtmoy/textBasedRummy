/**
* @file CardModelTest.cpp
* @author Spencer Taylor, Maruf Tonmoy, Muhammad Waleed.
* @date November 4th
*/


#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "CardModel.h"


TEST(CardModelTest, constructorTest) {
  CardModel cm(1, 1);
  EXPECT_EQ(cm.getRank(), 1);
  EXPECT_EQ(cm.getSuit(), 1);
  EXPECT_NE(cm.getRank(), 5);
}

TEST(CardModelTest, getNameTest) {
  CardModel cm(0, 0);
  EXPECT_EQ(cm.getRankName(), "Ace");
  EXPECT_EQ(cm.getSuitName(), "Hearts");
}
