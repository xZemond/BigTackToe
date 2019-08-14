#include "GameControl.h"




GameControl::GameControl(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2)
{
   //Initalization
   m_player[0] = player1;
   m_player[1] = player2;
   m_field = std::make_shared<Field>();
   player1->setField(m_field);
   player2->setField(m_field);
   m_rounds = 0;
}

GameControl::GameControl(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2, std::vector<std::vector<Color>> field)
{
   //Initalization (existing field template)
   m_player[0] = player1;
   m_player[1] = player2;
   m_field = std::make_shared<Field>(field);
   player1->setField(m_field);
   player2->setField(m_field);
   m_rounds = 0;
}

GameControl::~GameControl() {
}

Color GameControl::startGame()
{
   Color color;
   std::tuple<int, int> position;
   if (staticData::printEnabled) {
      m_field->printField();
   }
   do {
      //lets active Player move, and repeats if the picked positions is already set
      color = m_player[m_rounds % 2]->getColor();
      position = m_player[m_rounds % 2]->move();
      if (m_field->setStone(position, color)) {
         m_rounds += 1;
         if (staticData::printEnabled) {
            std::system("cls");
            m_field->printField();
         }
      }
      else {
         if (staticData::printEnabled) {
            std::cout << std::endl << "> Spot already full - try again ";
         }
      }

      //Returns Draw if every Spot is used
      if (m_rounds == (staticData::fieldSize) * (staticData::fieldSize)) {
         return Blank;
      }
   }
   while (!checkWin::all(color, position, m_field));

   //Returns Winner
   return m_player[m_rounds % 2]->getColor();
}

