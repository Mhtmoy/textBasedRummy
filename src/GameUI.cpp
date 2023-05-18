/**
* @file GameUI.cpp
* @author Mackenzie Kure
* @date Oct 13
*/
#include <iostream>
#include <GameUI.h>
#include <CardModel.h>
#include <vector>
#include <map>
#include <string>
/**
* @brief Constructor
*/
GameUI::GameUI() {}

GameUI::~GameUI() {}


/**
* @brief Displays opening statements and asks the user for the number of players
* gives option to display rules.
* @returns int the number of players the user inputed
*/
int GameUI::gameOpening() {
  std::string rules;
  std::string startG;
  int input;
  std::cout << "WELCOME TO THE GAME RUMMY!" << std::endl;
  std::cout << std::endl;
  std::cout << "before we begin would you like to hear the rules of rummy";
  std::cout << " (Yes or No ?) -- ";
  std::cin >> rules;
  if (rules == "Yes" || rules == "yes") {
    displayRules();
  }
  std::cout << std::endl;
  std::cout << "Use the command 'START' when you are ready to play rummy -- ";
  std::getline(std::cin, startG);
    do {
      std::cout << "try again: " << std::endl;
      std::getline(std::cin, startG);
  } while (startG != "START");
  std::cout << "Enter numer of players (2-4): ";
  std::cin >> input;
  while (input < 2 || input > 4) {
    std::cout << "Not valid, try again: ";
    std::cin >> input;
  }
  std::cout << std::endl;

  std::cout << "LET THE GAME BEGIN" << std::endl;
  std::cout << std::endl;

  return input;
}
/**
* @brief Displays a hand of cards
* @param[in] int player identifies the correct player's hands
* @param[in] map<int, std::vector<CardModel>> hands map of all the players hands
*/
void GameUI::displayHands(int player, std::map<int, std::vector<CardModel>>
                          hands) {
  CardModel tempCard;
  std::cout << "--------------------------------------------------------------";
  std::cout << std::endl;
  std::vector<CardModel> pHand = hands.at(player);
  std::cout << " The Cards in Player " << player + 1 << " 's hand are --- ";
  std::cout << std::endl;
  for (int i = 0; i < pHand.size(); ++i) {
    tempCard = pHand[i];

    std::string suit = tempCard.getSuitName();
    std::string rank = tempCard.getRankName();

    std::cout << i+1 << " [" << rank;
    std::cout << " Of " << suit <<  "]" << std::endl;
  }
  std::cout << "--------------------------------------------------------------";
  std::cout << std::endl;
}
/**
* @brief Displays all melds
* @param[in] map<int, std::vector<CardModel>> melds map of all the melds on the
*           table
*/
void GameUI::displayMelds(std::map<int, std::vector<CardModel>> allMelds) {
  std::map<int, std::vector<CardModel>>::iterator it;
  CardModel tempCard;
  std::cout << "--------------------------------------------------------------";
  std::cout << std::endl;
  std::cout << "CURRENT MELDS: " << std::endl;
  for (it = allMelds.begin(); it != allMelds.end(); ++it) {
    std::vector<CardModel> curMeld = it->second;
    int meldVal = it->first;

    std::cout << "#" << meldVal + 1 << " contains -- ";
    std::cout << std::endl;

    for (int i = 0; i < curMeld.size(); i++) {
      tempCard = curMeld[i];
      std::string suit = tempCard.getSuitName();
      std::string rank = tempCard.getRankName();

      std::cout << i+1 << " [" << rank;
      std::cout << " Of " << suit << "]" << std::endl;
    }
    std::cout << std::endl;
  }
  std::cout << "--------------------------------------------------------------";
  std::cout << std::endl;
}
/**
* @brief Displays top card of discard pile
* @param[in] vector<CardModel>  vector for the discard pile
*/
void GameUI::displayDiscardedDeck(std::vector<CardModel> discard) {
  std::cout << std::endl;
  std::cout << " The draw pile has a ";
  CardModel tempCard = discard.back();
  std::cout << "[" << tempCard.getRankName() << " of ";
  std::cout << tempCard.getSuitName();
  std::cout << "]" << std::endl;
  std::cout << "--------------------------------------------------------------";
  std::cout << std::endl;
}
/**
* @brief Displays the calculated scores of all players
* @param[in] map<int, int> players map of all the player's and their scores
*/
void GameUI::displayScore(std::map<int, int> players) {
  std::map<int, int>::iterator it;
  std::cout << "--------------------------------------------------------------";
  std::cout << std::endl;
  std::cout << "Score: " << std::endl;
  for (it = players.begin(); it != players.end(); ++it) {
    std::cout << "Player #" << it->first + 1 << ": " << it->second;
    std::cout << std::endl;
    }
}
/**
* @brief requests input from the user on which deck they would like to draw
*       from: discard pile or deck
* @param[in] vector<CardModel> deck the discard pile
* @returns int user's input
*/
int GameUI::pickupCardInput(std::vector<CardModel> deck) {
  int input;
  std::cout << "--------------------------------------------------------------";
  std::cout << std::endl;
  std::cout << "Draw from the deck or discard pile:" << std::endl;
  displayDiscardedDeck(deck);
  std::cout << "1. draw from deck" << std::endl;
  std::cout << "2. draw from discard pile" << std::endl;
  std::cout << "Enter input: ";
  std::cin >> input;
  while (input > 2) {
    std::cout << "not a valid input, try again: " << std::endl;
    std::cin >> input;
  }
  std::cout << "Card has been added to your hand" << std::endl;
  std::cout << std::endl;
  return input;
}
/**
* @brief asks the user to select a card they wish to discard, from numbered list
*        calls CardChoiceInput to take in user's input
* @param[in] int player identifies the correct player
* @param[in] map<int, vector<CardModel>> h all of the player's hands
* @returns the user's selection of card as an int
*/
int GameUI::discardCardInput(int ply, std::map<int, std::vector<CardModel>> h) {
  int input;
  std::cout << std::endl;
  std::cout << "Choose a card you wish to discard: " << std::endl;
  input = cardChoiceInput(ply, h);
  std::cout << "--------------------------------------------------------------";
  std::cout << std::endl;
  return input;
}
/**
* @brief asks the user to select a card they wish to discard, from numbered list
* @param[in] int player identifies the correct player
* @param[in] map<int, vector<CardModel>> hands all of the player's hands
* @returns the user's selection of card as an int
*/
int GameUI::cardChoiceInput(int player, std::map<int, std::vector<CardModel>>
                            hand) {
  int input;
  displayHands(player, hand);
  std::cout << std::endl;
  std::cout << " What card would you like to select (input the # not name) -- ";
  std::cin >> input;
  int size = hand.at(player).size();
  while (input > size) {
     std::cout << "Invalid option, try again:  ";
     std::cin >> input;
  }
  std::cout << "--------------------------------------------------------------";
  std::cout << std::endl;
    return input - 1;
}
/**
* @brief Asks player to enter the three card they wish to create a meld with
* @param[in] int player identifies the correct player
* @param[in] map<int, vector<CardModel>> hands all of the player's hands
* @returns cardChoice, a vector that contains all the users's chosen three cards
*/
std::vector<int> GameUI::meldChoiceInput(int player, std::map<int,
                                         std::vector<CardModel>> hand) {
  int input;
  displayHands(player, hand);
  std::vector<int> cardChoice;
  std::cout << "You will need to enter 3 cards you wish to make into a meld:";
  std::cout << std::endl;
  for (int i = 0; i < 3; i++) {
  std::cout << "Enter selection " << i + 1 << ": ";
  std::cin >> input;
  int size = hand.at(player).size();
      while (input > size) {
        std::cout << "Invalid option, try again:  ";
        std::cin >> input;
      }
      cardChoice.push_back(input - 1);
  }
  std::cout << "--------------------------------------------------------------";
  std::cout << std::endl;
  return cardChoice;
}
/**
* @brief allows player to select a meld from numbered list.
* @param[in] int player identifies the correct player
* @param[in] map<int, vector<CardModel>> meld all the melds on the table
* @returns an int representing their choice
*/
int GameUI::pickMeld(std::map<int, std::vector<CardModel>> meld) {
  int input;
  displayMelds(meld);
  std::cout << std::endl;
  std::cout << "Enter which meld you would like to add to: ";
  std::cin >> input;
  while (input > meld.size()) {
    std::cout << "Invalid option, try again:  ";
    std::cin >> input;
  }
  std::cout << "--------------------------------------------------------------";
  std::cout << std::endl;
  return input - 1;
}
/**
* @brief Displays the winner of the game
* @param[in] int winner the winning player
*/
void GameUI::displayWinner(int winner) {
  winner += 1;
  std::cout << " The winner of this game is -- Player #" << winner << std::endl;
  std::cout << "--------------------------------------------------------------";
  std::cout << std::endl;
  if (winner != 1) {
    std::cout << std::endl;
    std::cout << "You lost!" << std::endl;
    std::cout << std::endl;
  }
}
/**
* @brief Displays the rules of the game
*/
void GameUI::displayRules() {
std::cout << "The objective of the game is to get rid of your cards first";
std::cout << std::endl;
std::cout << "This is done through creating and adding to melds";
std::cout << "Form a meld of either: " << std::endl;
std::cout << "1. a run of three card of the same suit" << std::endl;
std::cout << "2. a set of three cards of the same rank" << std::endl;
std::cout << "On each turn the player has four step process: " << std::endl;
std::cout << "1. pick up a card from the deck or discard pile" << std::endl;
std::cout << "2. add to exiting melds" << std::endl;
std::cout << "3. create a new meld from three cards" << std::endl;
std::cout << "4. discard a card to end the turn, face up";
std::cout << " After a player discards,it is the next players turn";
std::cout << std::endl;
std::cout << " The play continues clockwise around the table." << std::endl;
std::cout << " When the stock runs out, shuffle the discard pile and";
std::cout << " set it up again. " << std::endl;
std::cout << "The first person to empty their hand, wins " << std::endl;
std::cout << std::endl;
}
/**
* @brief Display's an error message when create meld or add to meld cannot be
* completed.
*/
void GameUI::displayErrorMeld() {
  std::cout << std::endl;
  std::cout << "Meld could not be completed: invalid" << std::endl;
  std::cout << "--------------------------------------------------------------";
  std::cout << std::endl;
}
/**
* @brief Display's an error message when one cannot discard the card they just
* picked up from the discard pile
*/
void GameUI::displayErrorDiscard() {
  std::cout << std::endl;
  std::cout << "Cannot discard this card, picked it up this round" << std::endl;
  std::cout << "--------------------------------------------------------------";
  std::cout << std::endl;
}
/**
* @brief Display's an error message if there are no melds on the table
*/
void GameUI::emptyMeldsError() {
  std::cout << std::endl;
  std::cout << "No Melds Exist Yet" << std::endl;
  std::cout << "--------------------------------------------------------------";
  std::cout << std::endl;
}
/**
* @brief Display's for player's turn: meld create, meld add, discard and end
*       prompts the user for input
* @returns int of the user's input
*/
int GameUI::roundOptions() {
  int input;
  std::cout << "What would you like to do on your turn, make a selection: ";
  std::cout << std::endl;
  std::cout << "1. Add to meld" << std::endl;
  std::cout << "2. Create meld" << std::endl;
  std::cout << "3. discard and end turn" << std::endl;
  std::cout << "Enter selection: ";
  std::cin >> input;
  while (input > 3) {
    std::cout << "Invalid option, try again:  ";
    std::cin >> input;
  }
  std::cout << "--------------------------------------------------------------";
  std::cout << std::endl;
  return input;
}
/**
* @brief Display AI's turn for clarity
*/
void GameUI::AITurn(int player) {
  std::cout << std::endl;
  std::cout << "IT IS NOW PLAYER " << player + 1 << "'S TURN" << std::endl;
  std::cout << "--------------------------------------------------------------";
  std::cout << std::endl;
}
/**
* @brief Display AI's meld creationg for clarity
*/
void GameUI::achievedMeld(int player) {
  std::cout << "PLAYER " << player + 1 << " CREATED A MELD!" << std::endl;
}
