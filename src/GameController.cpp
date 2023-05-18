/**
* @file GameController.h
* @author Mackenzie Kure
* @date Oct 13
*/
#include <GameController.h>
#include <GameUI.h>
#include <DeckModel.h>
#include <CardModel.h>
#include <map>
#include <vector>
#include <algorithm>
#include <utility>
/**
* @brief Constrotor
*/
GameController::GameController(GameUI* ui, DeckModel* d) {
  deckptr = d;
  view = ui;
  numOfPlayers = view->gameOpening();
  deck = deckptr->createDeck();
  playerDeal();
}

void GameController::setView(GameUI* g) {
  view = g;
}

/**
* @brief picksup a card from deck or discard pile, card added to hand and
*        deleted from deck or discard pile
* @param[in] int userSelection user's choice for pickup
* @param[in] int player identifies the correct player
*/
void GameController::pickUpLogic(int userSelection, int playersHand) {
  if (userSelection == 1) {
    //takes card from top of the deck
    hands.at(playersHand).push_back(deck.back());
    deck.erase(deck.end());
  } else {
    //takes card form discard pile
    hands.at(playersHand).push_back(discard.back());
    discard.erase(discard.end());
    discardFlag = true;
  }
}
/**
* @brief Checks that the player may discard their card on the discard pile
* @returns false if this is an invalid move, returns true if valid
*/
bool GameController::discardCheckLogic() {
  if (discardFlag == true) {
      discardFlag = false;
      return false;
  } else {
      discardFlag = false;
      return true;
  }
}
/**
* @brief performs discard, increases either the discard pile or deck by one,
* and reduces the players hand by one.
* @param[in] int cardChoice the users chosen card to discard
* @param[in] int player identifies the correct player
*/
void GameController::discardLogic(int CardChoice, int playerHand) {
    //creating temp card to add to the discard pile
    CardModel temp = hands.at(playerHand).at(CardChoice);
    //adding Card to the discard pile;
    discard.push_back(temp);
    //created a temp vector to erase card from the players hand
    hands.at(playerHand).erase(hands.at(playerHand).begin() + (CardChoice));
}
/**
* Parameters: int for the user's meld selection, int representing the user's
* chosen card to add to the specified meld, and int to represent the player
* @brief attempts to add the user' chosen card to the meld they selected
* @param[in] int cardChoice the card the user wishes to add to the meld
* @param[in] int meldSelect the meld the user wishes to add to
* @param[in] int player identifies the correct player
*/
bool GameController::meldAddLogic(int Card, int meldSelect, int playerHand ) {
  CardModel tempCard = hands.at(playerHand).at(Card);
  std::vector<CardModel> m = melds.at(meldSelect);
  if (tempCard.getRank() == m.back().getRank() &&
      tempCard.getRank() == m.front().getRank()) {
    //adding the card to the meld
    melds.at(meldSelect).push_back(tempCard);
    //sorting the meld
    sort(melds.at(meldSelect));
    //removing the card added to the meld from the players hand
    hands.at(playerHand).erase(hands.at(playerHand).begin() + (Card));
    return true;
  } else if (tempCard.getSuit() == m.at(0).getSuit() &&
             tempCard.getSuit() == m.back().getSuit()) {
             if (tempCard.getRank() == m.at(0).getRank() - 1 ||
                tempCard.getRank() == m.back().getRank() + 1) {
                  //logical operations
                  melds.at(meldSelect).push_back(tempCard);
                  sort(melds.at(meldSelect));
                  //removing the card added to the meld from the players hand
              hands.at(playerHand).erase(hands.at(playerHand).begin() + (Card));
            } else {
              return false;
            }
  } else {
    // returns false b/c the card may not be added to this meld
    return false;
  }
}
/**
* @brief attempts to create a meld from  three cards
* @param[in] card1 card used to create the meld
* @param[in] card2 card used to create the meld
* @param[in] card3 card used to create the meld
* @param[in] player identifies the correct player
* @returns true if the meld was successfully completed, else returns false
*/
bool GameController::meldCreate(int card1, int card2, int card3, int player ) {
  //creating temp cards inorder to create a meld
  CardModel c1 = hands.at(player).at(card1);
  CardModel c2 = hands.at(player).at(card2);
  CardModel c3 = hands.at(player).at(card3);
  std::vector<CardModel> tempMeld;
  //checking if the meld is all the same rank
  if (c1.getRank() == c2.getRank() && c2.getRank() == c3.getRank() &&
      c3.getRank() == c1.getRank()) {
        tempMeld.push_back(c1);
        tempMeld.push_back(c2);
        tempMeld.push_back(c3);
        sort(tempMeld);
        melds[numOfMelds] = tempMeld;
        //number of melds increased, as one waws just added
        numOfMelds++;
        //begin sure to remove the smallest card first
        int smallest = checkSmallest(card1, card2, card3);
        int largest = checkLargest(card1, card2, card3);
        int middle = checkMiddle(card1, card2, card3);
          //removing cards made into meld from the players hand
          hands.at(player).erase(hands.at(player).begin() + smallest);
          hands.at(player).erase(hands.at(player).begin() + (middle - 1));
          hands.at(player).erase(hands.at(player).begin() + (largest - 2));

            return true;
        //checking if the meld is same suit and a run
      } else if (c1.getSuit() == c2.getSuit() && c2.getSuit() == c3.getSuit() &&
                  c3.getSuit() == c1.getSuit()) {
        int smallest = checkSmallest(c1.getRank(), c2.getRank(), c3.getRank());
        int largest = checkLargest(c1.getRank(), c2.getRank(), c3.getRank());
        int middle = checkMiddle(c1.getRank(), c2.getRank(), c3.getRank());
        if (smallest == middle - 1 && middle == largest -1) {
          tempMeld.push_back(c1);
          tempMeld.push_back(c2);
          tempMeld.push_back(c3);
          //sort(tempMeld);
          melds[numOfMelds] = tempMeld;
          sort(melds.at(numOfMelds));
          numOfMelds++;
          //begin sure to remove the smallest card first
          int smallest = checkSmallest(card1, card2, card3);
          int largest = checkLargest(card1, card2, card3);
          int middle = checkMiddle(card1, card2, card3);
            //removing cards made into meld from the players hand
            hands.at(player).erase(hands.at(player).begin() + smallest);
            hands.at(player).erase(hands.at(player).begin() + (middle - 1));
            hands.at(player).erase(hands.at(player).begin() + (largest - 2));
                  return true;
                } else {
                  return false;
                }
            } else {
               return false;
             }
}
/**
* @brief  returns the smallest of three integers
* @param[in] int num1
* @param[in] int num2
* @param[in] int num3
* @returns the smallest of the three integers
*/
int checkSmallest(int, int, int);
int GameController::checkSmallest(int num1, int num2, int num3) {;
    if (num2 < num1 && num2 < num3) {
      return num2;
    } else if (num3 < num1 && num3 < num2) {
      return num3;
    } else {
      return num1;
    }
}
/**
* @brief  returns the largest of three integers
* @param[in] int num1
* @param[in] int num2
* @param[in] int num3
* @returns the largest of the three integers
*/
int GameController::checkLargest(int num1, int num2, int num3) {
  if (num2 > num1 && num2 > num3) {
    return num2;
  } else if (num3 > num1 && num3 > num2) {
    return num3;
  } else {
    return num1;
  }
}
/**
* @brief  returns the middle of three integers
* @param[in] int num1
* @param[in] int num2
* @param[in] int num3
* @returns the middle of the three integers
*/
int GameController::checkMiddle(int num1, int num2, int num3) {
  if ((num1 < num2 && num2 < num3) || (num3 < num2 && num2 < num1)) {
    return num2;
  } else if ((num2 < num1 && num1 < num3) || (num3 < num1 && num1 < num2)) {
    return num1;
  } else {
    return num3;
  }
}
/**
* @brief Checks if the given players hand is empty
* @param[in] int playersHand identifies the correct player
* @returns true if hand is empty, else returns false
*/
bool GameController::endGameLogic(int playersHand) {
  if (hands.at(playersHand).size() == 0) {
    //sets who the winner is
    winner = playersHand;
    //if the playersHand is empty, they have won the game
    return true;
  } else {
    //if players hand is still full, returns false, they have not won
    return false;
  }
}
/**
* @brief Calculates the winners score by adding up the losers cards together
* @param[in] int winner identifies the winner
*/
void GameController::calculateScore(int winner) {
  int score = 0;
  for (auto it : hands) {
    for (int i = 0; i < it.second.size(); i++) {
      score += it.second.at(i).getRank();
    }
  }
  scoreTotals[winner] += score;
}
/**
* @brief deals out the hands, the size of the hand dependent on the number of
*       players, also deals out one card to the discard pile
*       initlizes map containing the palyers and their scores, which are zero
*/
void GameController::playerDeal() {
  // initializing vectors for the indiividual player's hands
  std::vector<CardModel> hand1;
  std::vector<CardModel> hand2;
  std::vector<CardModel> hand3;
  std::vector<CardModel> hand4;
  if (numOfPlayers == 2) {
    for (int numOfCards = 0; numOfCards < 10; numOfCards++) {
      // dealing out 10 cards each to the two players
        hand1.push_back(deckptr->deal(deck));
        hand2.push_back(deckptr->deal(deck));
    }
    //adding hands to the map of hands.
    hands[0] = hand1;
    hands[1] = hand2;
    scoreTotals[0] = 0;
    scoreTotals[1] = 0;
  } else if (numOfPlayers >= 3) {
    for (int numOfCards = 0; numOfCards < 7; ++numOfCards) {
      if (numOfPlayers == 3) {
        // dealing out 7 cards each to the three players
        hand1.push_back(deckptr->deal(deck));
        hand2.push_back(deckptr->deal(deck));
        hand3.push_back(deckptr->deal(deck));
      } else {
        // dealing out 7 cards each to the four players
        hand1.push_back(deckptr->deal(deck));
        hand2.push_back(deckptr->deal(deck));
        hand3.push_back(deckptr->deal(deck));
        hand4.push_back(deckptr->deal(deck));
      }
    }
    //adding hands to the map of hands.
    hands[0] = hand1;
    hands[1] = hand2;
    hands[2] = hand3;
    hands[3] = hand4;
    scoreTotals[0] = 0;
    scoreTotals[1] = 0;
    scoreTotals[2] = 0;
    scoreTotals[3] = 0;
  }
  //adding one card to the disCard pile
  discard.push_back(deckptr->deal(deck));
}
/**
* @brief Sorts hands by suit and then rank
* @param[in] std::vector<CardModel>& hand the hand that is going to be sorted
*/
void GameController::sort(std::vector<CardModel>& hand) {
    std::sort(hand.begin(), hand.end(), [] (CardModel c1, CardModel c2 ) {
              return std::make_pair(c1.getSuit(), c1.getRank()) <
                     std::make_pair(c2.getSuit(), c2.getRank()); });
}
/**
* @brief Runs the game sequence, depends on the number of players
*/
void GameController::Game() {
  bool flag = false;
  if (numOfPlayers == 2) {
    while (flag != true) {
      flag = playerTurn(0);
      if (flag == true) {
        break;
      }
      flag = AITurn(1);
      if (flag == true) {
        break;
      }
    }
  } else if (numOfPlayers == 3) {
    while (flag != true) {
      flag = playerTurn(0);
      if (flag == true) {
        break;
      }
      flag = AITurn(1);
      if (flag == true) {
        break;
      }
      flag = AITurn(2);
      if (flag == true) {
        break;
      }
    }
  } else {
    while (flag != true) {
      flag = playerTurn(0);
      if (flag == true) {
        break;
      }
      flag = AITurn(1);
      if (flag == true) {
        break;
      }
      flag = AITurn(2);
      if (flag == true) {
        break;
      }
      flag = AITurn(3);
      if (flag == true) {
        break;
      }
    }
  }
  calculateScore(winner);
  view->displayWinner(winner);
  view->displayScore(scoreTotals);
}
/**
* @brief Runs the sequence of the the players turn: pick-up, option to meld,
*        add to meld, discard, checks if game is ended.
* @param[in] int player identifies the correct player
* @returns true if the player's hand is empty, else false
*/
bool GameController::playerTurn(int player) {
  int CardChoice = 0;
  //sort player's hand at the beginning of each turn
  sort(hands.at(player));
  //display the player's hand
  view->displayHands(player, hands);
  //player told the top card of the discard pile
  //player chooses pickup from deck or discard pile
  int choice =  view->pickupCardInput(discard);
  //player's chosen card is added to their hand and deleted from the correct
  // vector: discard or deck
  pickUpLogic(choice, player);
  //display the melds to that the player may make a choice
  view->displayMelds(melds);
  //the players hand is displayed
  view->displayHands(player, hands);
  //player is asked what they would like to do on their turn
  choice = view->roundOptions();
     while (choice != 3) {
        //Selection for meldAdd
        if (choice == 1) {
          if (melds.size() == 0) {
            view->emptyMeldsError();
          } else {
            //retrieves users choce of meld they wish to add to
            choice = view->pickMeld(melds);
            // gets players choice of card they wish to add to the meld
            CardChoice = view->cardChoiceInput(player, hands);
            // attmpts to add the chosen card to the chosen meld
            if (meldAddLogic(CardChoice, choice, player)) {
              //error is displayed if the meld cannot be completed
              view->displayMelds(melds);
            } else {
                view->displayErrorMeld();
            }
          }
        } else if (choice == 2) {
              // takes in the users input of three cards to make a meld
              std::vector<int> meldCards = view->meldChoiceInput(player, hands);
            //Checks to see if the meld may actually be completed
            if (meldCreate(meldCards.at(0), meldCards.at(1), meldCards.at(2),
                player) == false) {
                //of meld cannot be created, returns an error.
                view->displayErrorMeld();
              }
              view->achievedMeld(player);
              view->displayMelds(melds);
           }
           //Asks for round options once more
           choice = view->roundOptions();
      }
      //Discard Process
      bool flag = discardCheckLogic();
      do {
        CardChoice =  view->discardCardInput(player, hands);
        flag = discardCheckLogic();
      } while (flag = false);
      discardLogic(CardChoice, player);

  if (endGameLogic(player) == true) {
        return true;
  } else {
     return false;
  }
}
/**
* @brief Runs the AI's turn: pickup, check for melds, meld, discard, check if
*  AI's hand is empty
* @param[in] int player identifies the correct AI player
* @returns true if AI's hand is empty, else false
*/
bool GameController::AITurn(int player) {
view->AITurn(player);
view->displayDiscardedDeck(discard);
pickUpLogic(2, player);
meldSearch(player);
meldAddSearch(player);
discardLogic(0, player);
  if (endGameLogic(player) == true) {
      return true;
  } else {
      return false;
  }
}
/**
* @brief looks for melds in the AI's hand
* @param[in] int player identifies the correct AI player
*/
void GameController::meldSearch(int player) {
for (int i = 0; i < hands.at(player).size() - 2; i++) {
  for (int j = 1; j < hands.at(player).size() - 1; j++) {
    if (j == i || j < i) {
      continue;
    }
  for (int k = 2; k < hands.at(player).size(); k++) {
      if (j == k || k < j) {
        continue;
      }
       meldCreate(i, j, k, player);
  }
  }
}
}
/**
* @brief attempts to add all of AI's cards to all exisiting melds
* @param[in] nt player identifies the correct AI player
*/
void GameController::meldAddSearch(int player) {
  for (int i = 0; i < hands.at(player).size(); i++) {
    for (int m = 0; m < numOfMelds; m++) {
      if (meldAddLogic(i, m, player)) {
        break;
      }
    }
  }
}

int GameController::getHandSize(std::vector<CardModel> h) {
  return (h.size());
}

std::map <int, std::vector<CardModel>> GameController::getHands() {
  return hands;
}
