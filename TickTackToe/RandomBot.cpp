#include "RandomBot.h"

RandomBot::RandomBot(Color color)
   : Player(color) {
}

RandomBot::~RandomBot() {
}

std::tuple<int, int> RandomBot::move() const
{
   //gets List with available spots
   auto blankList = m_field->getBlankList();
   //choses random element of the List
   return *std::next(blankList.begin(), std::rand() % blankList.size());
}
