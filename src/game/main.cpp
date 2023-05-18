#include <iostream>
#include <GameController.h>

int main() {
  GameUI* ui = new GameUI();
  DeckModel* d = new DeckModel();

  GameController game(ui, d);
  game.Game();


return 0;
}
