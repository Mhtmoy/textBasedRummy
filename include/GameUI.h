/**
* @file GameUI.h
* @author Mackenzie Kure
* @date Oct 13
*/
#ifndef GAMEUI_H
#define GAMEUI_H

#include <iostream>
#include <CardModel.h>
#include <map>
#include <vector>
#include <string>

class GameUI {
 public:
   /**
   * @brief Constructor
   */
  GameUI();


  virtual ~GameUI();
  /**
  * @brief Displays opening statements and asks the user for the number of players
  * gives option to display rules.
  */
  virtual int gameOpening();
  /**
  * @brief Displays a hand of cards
  * @param[in] int player identifies the correct player's hands
  * @param[in] map<int, std::vector<CardModel>> hands map of all the players hands
  */
  virtual void displayHands(int, std::map<int, std::vector<CardModel>>);
  /**
  * @brief Displays all melds
  * @param[in] map<int, std::vector<CardModel>> melds map of all the melds on the
  *           table
  */
  virtual void displayMelds(std::map<int, std::vector<CardModel>>);
  /**
  * @brief Displays top card of discard pile
  * @param[in] vector<CardModel>  vector for the discard pile
  */
  virtual void displayDiscardedDeck(std::vector<CardModel>);
  /**
  * @brief Displays the calculated scores of all players
  * @param[in] map<int, int> players map of all the player's and their scores
  */
  virtual void displayScore(std::map<int, int>);
  /**
  * @brief requests input from the user on which deck they would like to draw
  *       from: discard pile or deck
  * @param[in] vector<CardModel> deck the discard pile
  * @returns int user's input
  */
  virtual int pickupCardInput(std::vector<CardModel>);
  /**
  * @brief asks the user to select a card they wish to discard, from numbered list
  * @param[in] int player identifies the correct player
  * @param[in] map<int, vector<CardModel>> all of the player's hands
  * @returns the user's selection of card as an int
  */
  virtual int discardCardInput(int, std::map<int, std::vector<CardModel>>);
  /**
  * @brief asks the user to select a card they wish to discard, from numbered list
  * @param[in] int player identifies the correct player
  * @param[in] map<int, vector<CardModel>> hands all of the player's hands
  * @returns the user's selection of card as an int
  */
  virtual int cardChoiceInput(int, std::map<int, std::vector<CardModel>>);
  /**
  * @brief Asks player to enter the three card they wish to create a meld with
  * @param[in] int player identifies the correct player
  * @param[in] map<int, vector<CardModel>> hands all of the player's hands
  * @returns cardChoice, a vector that contains all the users's chosen three cards
  */
  virtual std::vector<int>
    meldChoiceInput(int, std::map<int, std::vector<CardModel>>);
  /**
  * @brief allows player to select a meld from numbered list.
  * @param[in] int player identifies the correct player
  * @param[in] map<int, vector<CardModel>> meld all the melds on the table
  * @returns an int representing their choice
  */
  virtual int pickMeld(std::map<int, std::vector<CardModel>>);
  /**
  * @brief Displays the winner of the game
  * @param[in] int winner the winning player
  */
  virtual void displayWinner(int);
  /**
  * @brief Displays the rules of the game
  */
  virtual void displayRules();
  /**
  * @brief Display's an error message when create meld or add to meld cannot be
  * completed.
  */
  virtual void displayErrorMeld();
  /**
  * @brief Display's an error message when one cannot discard the card they just
  * picked up from the discard pile
  */
  virtual void displayErrorDiscard();
  /**
  * @brief Display's an error message if there are no melds on the table
  */
  virtual void emptyMeldsError();
  /**
  * @brief Display's for player's turn: meld create, meld add, discard and end
  *       prompts the user for input
  * @returns int of the user's input
  */
  virtual int roundOptions();
  /**
  * @brief Display AI's turn for clarity
  */
  virtual void AITurn(int);
  /**
  * @brief Display AI's meld creationg for clarity
  */
  virtual void achievedMeld(int);
};
#endif
