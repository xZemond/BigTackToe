#include "Field.h"

Field::Field()
{
   //resizes vector to field size
   m_field.resize(staticData::fieldSize);
   for (int i = 0; i < staticData::fieldSize; i++) {
      m_field[i].resize(staticData::fieldSize);
      //sets every element to 'blank'
      std::fill(m_field[i].begin(), m_field[i].end(), Blank);
   }

   //adds tuples with coordinates to List that stored every Blank Spot
   for (int i = 0; i < staticData::fieldSize; i++) {
      for (int j = 0; j < staticData::fieldSize; j++)
         m_blankList.push_back(std::make_tuple(j, i));
   }   
}

Field::Field(std::vector<std::vector<Color>> field) {
   //creates field with existing pattern
   m_field = field;

   //adds tuples with coordinates to List that stored every Blank Spot
   for (int i = 0; i < staticData::fieldSize; i++) {
      for (int j = 0; j < staticData::fieldSize; j++) {
         if (m_field[i][j] == Blank) {
            m_blankList.push_back(std::make_tuple(j, i));
         }
      }
   }
}


Field::~Field() {
}

std::vector<std::vector<Color>> Field::getField() {
   return m_field;
}

Color Field::getStone(int xCord, int yCord) const {
   return m_field[xCord][yCord];
}

std::list<std::tuple<int, int>> Field::getBlankList() const {
   return m_blankList;
}

bool Field::setStone(std::tuple<int, int> cords, Color color)
{
   //sets Stone if the spot is 'Blankk'
   if (m_field[std::get<0>(cords)][std::get<1>(cords)] == Blank) {
      m_field[std::get<0>(cords)][std::get<1>(cords)] = color;
      //removes the spot from the BlankList
      m_blankList.remove(cords);
      return true;
   }
   return false;
}

void Field::printField() const
{
   for (int i = 0; i <= staticData::fieldSize; i++) {

      std::cout << std::endl << std::endl << "  " << i << " ";
      for (int j = 0; j < staticData::fieldSize ; j++) {
         if (i == 0) {
            std::cout << "  " << j + 1 << " " ;
         }
         else {
            switch (m_field[i - 1][j]) {
               case Blank:
                  std::cout << "    ";
                  break;
               case Cross:
                  std::cout << "  X ";
                  break;
               case Circle:
                  std::cout << "  O ";
                  break;
            }
         }
      }
   }
}


