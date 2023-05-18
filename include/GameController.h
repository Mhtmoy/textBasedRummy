/**
* @file GameController.h
* @author Mackenzie Kure
* @date Oct 13
*/

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <DeckModel.h>
#include <GameUI.h>
#include <iterator>
#include <map>
#include <vector>
#include <algorithm>

class GameController {
 public:
  /**
  * @brief Constrotor
  */
  GameController(GameUI*, DeckModel*);
  /**
  * @brief picksup a card from deck or discard pile, card added to hand and
  *        deleted from deck or discard pile
  * @param[in] int userSelection user's choice for pickup
  * @param[in] int player identifies the correct player
  */
  void pickUpLogic(int, int);
  /**
  * @brief Checks that the player may discard their card on the discard pile
  * @returns false if this is an invalid move, returns true if valid
  */
  bool discardCheckLogic();
  /**
  * @brief performs discard, increases either the discard pile or deck by one,
  * and reduces the players hand by one.
  * @param[in] int cardChoice the users chosen card to discard
  * @param[in] int player identifies the correct player
  */
  void discardLogic(int, int);
  /**
  * Parameters: int for the user's meld selection, int representing the user's
  * chosen card to add to the specified meld, and int to represent the player
  * @brief attempts to add the user' chosen card to the meld they selected
  * @param[in] int cardChoice the card the user wishes to add to the meld
  * @param[in] int meldSelect the meld the user wishes to add to
  * @param[in] int player identifies the correct player
  * @returns true if the lay off was successful, false if the lay off was
  *          invalid
  */
  bool meldAddLogic(int, int, int);
  /**
  * @brief attempts to create a meld from  three cards
  * @param[in] card1 card used to create the meld
  * @param[in] card2 card used to create the meld
  * @param[in] card3 card used to create the meld
  * @param[in] player identifies the correct player
  * @returns true if the meld was successfully completed, else returns false
  */
  bool meldCreate(int, int, int, int);
  /**
  * @brief  returns the smallest of three integers
  * @param[in] int num1
  * @param[in] int num2
  * @param[in] int num3
  * @returns the smallest of the three integers
  */
  int checkSmallest(int, int, int);
  /**
  * @brief  returns the largest of three integers
  * @param[in] int num1
  * @param[in] int num2
  * @param[in] int num3
  * @returns the largest of the three integers
  */
  int checkLargest(int, int, int);
  /**
  * @brief  returns the middle of three integers
  * @param[in] int num1
  * @param[in] int num2
  * @param[in] int num3
  * @returns the middle of the three integers
  */
  int checkMiddle(int, int, int);
  /**
  * @brief Checks if the given players hand is empty
  * @param[in] int playersHand identifies the correct player
  * @returns true if hand is empty, else returns false
  */
  bool endGameLogic(int);
  /**
  * @brief Calculates the winners score by adding up the losers cards together
  * @param[in] int winner identifies the winner
  */
  void calculateScore(int);
  /**
  * @brief deals out the hands, the size of the hand dependent on the number of
  *       players, also deals out one card to the discard pile
  *       initlizes map containing the palyers and their scores, which are zero
  */
  void playerDeal();
  /**
  * @brief Sorts hands by suit and then rank
  * @param[in] std::vector<CardModel>& hand the hand that is going to be sorted
  */
  void sort(std::vector<CardModel>&);
  /**
  * @brief Runs the game sequence, depends on the number of players
  */
  void Game();
  /**
  * @brief Runs the sequence of the the players turn: pick-up, option to meld,
  *        add to meld, discard, checks if game is ended.
  * @param[in] int player identifies the correct player
  * @returns true if the player's hand is empty, else false
  */
  bool playerTurn(int);
  /**
  * @brief Runs the AI's turn: pickup, check for melds, meld, discard, check if
  *  AI's hand is empty
  * @param[in] int player identifies the correct AI player
  * @returns true if AI's hand is empty, else false
  */
  bool AITurn(int);
  /**
  * @brief looks for melds in the AI's hand
  * @param[in] int player identifies the correct AI player
  */
  void meldSearch(int player);
  /**
  * @brief attempts to add all of AI's cards to all exisiting melds
  * @param[in] nt player identifies the correct AI player
  */
  void meldAddSearch(int player);

  void setView(GameUI*);

  int getHandSize(std::vector<CardModel>);

  std::map <int, std::vector<CardModel>> getHands();
  int getNumberOfPlayers() {
    return numOfPlayers;
  }
bool getDiscardFlag() {
  return discardFlag;
}

 private:
  std::vector<CardModel> discard;
  DeckModel* deckptr;
  GameUI* view;
  std::vector<CardModel> deck;
  int numOfMelds = 0;
  int numOfPlayers = 0;
  bool discardFlag = false;
  std::map <int, std::vector<CardModel>> hands;
  std::map <int, std::vector<CardModel>> melds;
  int winner  = 0;
  std::map <int, int> scoreTotals;
};
#endif
