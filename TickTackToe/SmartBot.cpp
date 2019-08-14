#include "SmartBot.h"

SmartBot::SmartBot(Color color)
   : Player(color) {
}

SmartBot::~SmartBot() {
}

std::tuple<int, int> SmartBot::move() const
{
   auto const blankList = m_field->getBlankList();
   //copy Field
   std::vector<std::vector<Color>> tmpField(staticData::fieldSize, std::vector<Color>(staticData::fieldSize));
   for (int i = 0; i < staticData::fieldSize; i++) {
      for (int j = 0; j < staticData::fieldSize; j++) {
         tmpField[i][j] = m_field->getStone(i, j);
      }
   }
   //checks if it can win in one turn
   for (auto iter = blankList.begin(); iter != blankList.end(); iter++) {
      auto tmpField2 = std::make_shared<Field>(tmpField);
      tmpField2->setStone(*iter, m_color);
      if (checkWin::all(m_color, *iter, tmpField2)) {
         return *iter;
      }
   }

   //checks if the enemy can win in one turn
   for (auto iter = blankList.begin(); iter != blankList.end(); iter++) {
      Color tmpColor;
      if (m_color == Circle) tmpColor = Cross;
      else tmpColor = Circle;
      auto tmpField2 = std::make_shared<Field>(tmpField);
      tmpField2->setStone(*iter, tmpColor);
      if (checkWin::all(tmpColor, *iter, tmpField2)) {
         return *iter;
      }
   }

   /*In Case noone can win: */

   /*move like the Stupid Bot, but backwards --> stronger against the bots, but very easy to outplay as human */
   //return blankList.back();

   /* move randomly --> a bit weaker against the bots, stronger against a human (actually pretty hard to win against it) */
   /* I'll leave this one active 'cause he's funnier */
   return *std::next(blankList.begin(), std::rand() % blankList.size());
}

