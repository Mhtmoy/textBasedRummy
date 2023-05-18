/**
* @file CardModel.h
* @author Mackenzie Kure
* @date Oct 13
*/

#ifndef CardModel_H
#define CardModel_H

#include <iostream>
#include <string>

class CardModel {
 public:
  //Variable Declarations: Arrays for the suit and rank
  std::string Rank[13] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10",
   "Jack", "Queen", "King"};
  std::string Suit[4] = {"Hearts", "Diamonds", "Spades", "Clubs"};
  /**
   * @brief Default Constructor
   */
CardModel();
  /**
   * @brief Constructor
   * @param[in] int r the suit of the card
   * @param[in] int s the suit of the card
   */
CardModel(int, int);
  /**
   *  @brief CardModel Destructor
   */
virtual  ~CardModel();
  /**
   * @brief returns the index of the suit
   * @returns suit index
   */
virtual  int getSuit();
  /**
   * @brief returns the index of the rank
   * @returns rank index
   */
virtual  int getRank();
  /**
   * @brief returns the name of of the suit
   * @returns name of suit
   */
virtual  std::string getSuitName();
  /**
   * @brief returns the name of of the rank
   * @returns name of rank
   */
virtual  std::string getRankName();

virtual  bool operator==(const CardModel& c) const {
    return true;
  }

 private:
  int suitNum = 0;
  int rankNum = 0;
};
#endif
