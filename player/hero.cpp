#include <iostream>
#include "hero.h"

Hero::Hero(char const* n, int s,
           unsigned lvl) : level(lvl), Player(n, s) {
}

void Hero::print(std::ostream& os) const {
  Player::print();
  os << " и е герой на ниво " << getLevel();
}

std::ostream& operator<<(std::ostream& os, Hero const& h) {
  h.print(os);
  return os << std::endl;
}
