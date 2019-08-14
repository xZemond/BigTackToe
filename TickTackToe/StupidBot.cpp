#include "StupidBot.h"

StupidBot::StupidBot(Color color)
   : Player(color) {
}

StupidBot::~StupidBot() {
}

std::tuple<int, int> StupidBot::move() const {
   return m_field->getBlankList().front();
}
