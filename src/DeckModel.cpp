/**
* @file DeckModel.cpp
* @author Mackenzie Kure
* @date Oct 13
*/
#include <DeckModel.h>
#include <CardModel.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
/**
* @brief Constructor
*/
DeckModel::DeckModel() {
  deck = createDeck();
}
/**
 * @brief default Constructor
 */
DeckModel::~DeckModel() {}
/**
 * @brief deals out a single card from the deck
 * @param[in] std::vector<CardModel>& deckVec representing the deck of cards
 * @param[out] CardModel
 */
CardModel DeckModel::deal(std::vector<CardModel>& deckVec) {
  CardModel temp = deckVec.at(0);
  deckVec.erase(deckVec.begin());
  return temp;
}
/**
* @brief returns the deck of cards (CardModel)
* @param[out] deck
*/
std::vector<CardModel> DeckModel::getDeck() {
  return deck;
}
/**
* @brief Shuffles the vector of cards
* @param[in] std::vector<CardModel>&  deck of cards
*/
void DeckModel::shuffle(std::vector<CardModel>& deckVec) {
  srand(time(NULL));
  random_shuffle(deckVec.begin(), deckVec.end());
}
/**
* @brief populates a vector of cards, to represent a deck of cards
*/
std::vector<CardModel> DeckModel::createDeck() {
  std::vector<CardModel> newDeck;
    for (int rank = 0; rank < 13; rank++) {
       for (int suit = 0; suit < 4; suit++) {
         CardModel CardModel(rank, suit);
         newDeck.push_back(CardModel);
       }
    }
    shuffle(newDeck);
    return newDeck;
}
