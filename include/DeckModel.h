/**
* @file DeckModel.h
* @author Mackenzie Kure
* @date Oct 13
*/
#ifndef DeckModel_H
#define DeckModel_H

#include <CardModel.h>
#include <DeckModel.h>
#include <vector>

class DeckModel {
 public:
  /**
  * @brief Constructor
  */
  DeckModel();
  /**
   * @brief default Constructor
   */
  virtual ~DeckModel();
  /**
   * @brief deals out a single card from the deck
   * @param[in] std::vector<CardModel>& deckVec representing the deck of cards
   * @param[out] CardModel
   */
  virtual CardModel deal(std::vector<CardModel>&);
  /**
  * @brief returns the deck of cards (CardModel)
  * @param[out] deck
  */
  virtual std::vector<CardModel> getDeck();
  /**
  * @brief Shuffles the vector of cards
  * @param[in] std::vector<CardModel>&  deck of cards
  */
  virtual void shuffle(std::vector<CardModel>&);
  /**
  * @brief populates a vector of cards, to represent a deck of cards
  */
  virtual std::vector<CardModel> createDeck();

 private:
  std::vector<CardModel> deck;
};
#endif
