#include "enum.hpp"

int main() {
  SpielFeld jeux1;
  jeux1.initialize(15);

  jeux1.display(false);
  // SpielFeld jeux2;
  // jeux2.display(true);
  int playTime = jeux1.verbleibendeFelder_;
  while (playTime > 0) {
    bool state = jeux1.eingabe();
    if (state) {
      printf("!!!!!!!!!!!!! BOOOOMMMMMMMMMM !!!!!!!!!!!!!\n");
    }
    if (jeux1.verbleibendeFelder_ <= 0) {
      printf(" *|* *|* *|* *|*  Du hast gewonnen *|* *|* *|* *|* \n");
      break;
    }
    if (jeux1.score_ < 0) {
      printf("\n");
      printf("Du hast leider verloren !\n");
      break;
    }
    playTime--;
  }

  return 0;
}