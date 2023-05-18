/**
* @file CardModel.h
* @author Mackenzie Kure
* @date Oct 13
*/
#include <CardModel.h>
#include <string>
/**
 * @brief Default Constructor
 */
CardModel::CardModel() {}
/**
 * @brief Constructor
 * @param[in] int r the suit of the card
 * @param[in] int s the suit of the card
 */
CardModel::CardModel(int r, int s) {
  suitNum = s;
  rankNum = r;
}
/**
 *  @brief CardModel Destructor
 */
CardModel::~CardModel() {}
/**
 * @brief returns the index of the suit
 * @param[out] suit index
 */
int CardModel::getSuit() {
  return suitNum;
}
/**
 * @brief returns the index of the rank
 * @param[out] rank index
 */
int CardModel::getRank() {
  return rankNum;
}
/**
 * @brief returns the name of of the suit
 * @param[out] name of suit
 */
std::string CardModel::getSuitName() {
  return Suit[suitNum];
}
/**
 * @brief returns the name of of the rank
 * @param[out] name of rank
 */
std::string CardModel::getRankName() {
  return Rank[rankNum];
}
