/**
* @file GameControllerTest.cpp
* @author Spencer Taylor, Maruf Tonmoy, Muhammad Waleed.
* @date November 4th
*/
#include <map>
#include <vector>
#include <string>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "GameController.h"
#include "CardModel.h"


using ::testing::Expectation;
using ::testing::Return;

class MockCardModel : public CardModel {
 public:
  explicit MockCardModel() {}
  virtual ~MockCardModel() {}
  MOCK_METHOD0(getRankName, std::string());
};

class MockDeck : public DeckModel {
 public:
  explicit MockDeck() {}
  virtual ~MockDeck() {}

  MOCK_METHOD1(deal, CardModel(std::vector<CardModel>&));
  MOCK_METHOD0(getDeck, std::vector<CardModel>());
  MOCK_METHOD1(shuffle, void(std::vector<CardModel>&));
  MOCK_METHOD0(createDeck, std::vector<CardModel>());
};

class MockGameUI : public GameUI {
 public:
  explicit MockGameUI() {}
  virtual ~MockGameUI() {}

  MOCK_METHOD0(gameOpening, int());
  MOCK_METHOD2(displayHands, void(int, std::map<int, std::vector<CardModel>>));
  MOCK_METHOD1(displayMelds, void(std::map<int, std::vector<CardModel>>));
  MOCK_METHOD1(displayDiscardedDeck, void(std::vector<CardModel>));
  MOCK_METHOD1(displayScore, void(std::map<int, int>));
  MOCK_METHOD1(pickupCardInput, int(std::vector<CardModel>));
  MOCK_METHOD2(discardCardInput, int(int, std::map<int,
     std::vector<CardModel>>));
  MOCK_METHOD2(cardChoiceInput, int(int, std::map<int,
     std::vector<CardModel>>));
  MOCK_METHOD2(meldChoiceInput,
     std::vector<int>(int, std::map<int, std::vector<CardModel>>));
  MOCK_METHOD1(pickMeld, int(std::map<int, std::vector<CardModel>>));
  MOCK_METHOD1(displayWinner, void(int));
  MOCK_METHOD0(displayRules, void());
  MOCK_METHOD0(roundOptions, int());
};



TEST(GameControllerTest, GameControllerTestFunction) {
  MockDeck* deck = new MockDeck();
  MockGameUI* ui = new MockGameUI();
//  DeckModel* d = new DeckModel();
//  std::vector<CardModel> c;


/*  Expectation create = EXPECT_CALL(*deck, createDeck())
  .Times(1);
*/
  Expectation opening = EXPECT_CALL(*ui, gameOpening())
  .Times(1)
  .WillOnce(Return(2));


//  Expectation deal = EXPECT_CALL(*deck, deal(deck))
//  .Times(AnyNumber());
//GameController gc(ui, d);
GameController gc(ui, deck);
EXPECT_EQ(gc.getNumberOfPlayers(), 2);
  delete deck;
  delete ui;
  //delete d;
}


TEST(GameControllerTest, discardCheckLogic) {
  MockDeck* deck = new MockDeck();
  MockGameUI* ui = new MockGameUI();
  DeckModel* d = new DeckModel();

  Expectation opening = EXPECT_CALL(*ui, gameOpening())
  .Times(1)
  .WillOnce(Return(2));

  GameController gc(ui, deck);
  EXPECT_TRUE(gc.discardCheckLogic());

  delete deck;
  delete ui;
  delete d;
}

TEST(GameControllerTest, pickUpLogic) {
  MockDeck* deck = new MockDeck();
  MockGameUI* ui = new MockGameUI();
GameController gc(ui, deck);

gc.pickUpLogic(2,1);
EXPECT_TRUE(gc.getDiscardFlag());

delete ui;
}
TEST(GameControllerTest, checkSmallestTest) {
  MockGameUI* ui = new MockGameUI();
  DeckModel* d = new DeckModel();
  GameController gc(ui, d);

  EXPECT_EQ(gc.checkSmallest(1, 2, 3), 1);
  EXPECT_EQ(gc.checkSmallest(2, 1, 3), 1);
  EXPECT_EQ(gc.checkSmallest(2, 3, 1), 1);

  delete ui;
  delete d;
}

TEST(GameControllerTest, checkLargestTest) {
  MockGameUI* ui = new MockGameUI();
  DeckModel* d = new DeckModel();
  GameController gc(ui, d);

  EXPECT_EQ(gc.checkLargest(1, 2, 3), 3);
  EXPECT_EQ(gc.checkLargest(1, 3, 2), 3);
  EXPECT_EQ(gc.checkLargest(3, 2, 1), 3);

  delete ui;
  delete d;
}

TEST(GameControllerTest, checkMiddleTest) {
  MockGameUI* ui = new MockGameUI();
  DeckModel* d = new DeckModel();
  GameController gc(ui, d);

  EXPECT_EQ(gc.checkMiddle(2, 1, 3), 2);
  EXPECT_EQ(gc.checkMiddle(1, 2, 3), 2);
  EXPECT_EQ(gc.checkMiddle(1, 3, 2), 2);

  delete ui;
  delete d;
}
/*
TEST(GameControllerTest, playerDealTest) {
  MockDeck* d = new MockDeck();
  MockGameUI* ui = new MockGameUI();
  //DeckModel* dm = new DeckModel();
  //std::vector<CardModel> cm;
  //cm = dm->createDeck();
  //CardModel c = CardModel(1,1);

  Expectation opening = EXPECT_CALL(*ui, gameOpening())
  .Times(1)
  .WillOnce(Return(2));


  Expectation deal = EXPECT_CALL(*d, deal(cm))
 .Times(20)
 .WillOnce(Return(c))
 .WillRepeatedly(Return(c));


  GameController gc(ui, d);
  EXPECT_EQ(gc.getHandSize(gc.getHands()[0]), 10);
  EXPECT_EQ(gc.getHandSize(gc.getHands()[1]), 10);
  delete d;
  delete ui;
//  delete dm;
}

TEST(GameControllerTest, playerTurnTest) {
  MockDeck* d = new MockDeck();
  MockGameUI* ui = new MockGameUI();
  std::vector<CardModel> cm;
  CardModel c = CardModel(1,1);
  cm.push_back(c);
  std::map<int, std::vector<CardModel>> mp;



  Expectation opening = EXPECT_CALL(*ui, gameOpening())
  .Times(1)
  .WillOnce(Return(2));


  Expectation pickUp = EXPECT_CALL(*ui, pickupCardInput(cm))
  .Times(1)
  .WillOnce(Return(1));

  Expectation options = EXPECT_CALL(*ui, roundOptions())
  .Times(1)
  .WillOnce(Return(3));

  Expectation discard = EXPECT_CALL(*ui, discardCardInput(1,mp))
  .Times(1)
  .WillOnce(Return(1));

  GameController gc(ui, d);
  gc.Game();


  delete d;
  delete ui;
}
*/
