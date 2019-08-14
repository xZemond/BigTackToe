#include "Human.h"

Human::Human(Color color)
   : Player(color) {
}

Human::~Human() {
}

std::tuple<int, int> Human::move() const
{
   int xCord;
   int yCord;
   //gets x Cord
   std::cout << std::endl << "\n> Set x-Coordinate: ";
   std::cin >> xCord;
   std::cin.clear();
   std::cin.ignore();
   while (true) {
      if (xCord > 0 && xCord <= staticData::fieldSize) {
         break;
      }
      std::cout<< "> Invalid entry - try again: ";
      std::cin >> xCord;
      std::cin.clear();
      std::cin.ignore();
   }
   //gets y Cord
   std::cout << "> Set y-Coordinate: ";
   std::cin >> yCord;
   std::cin.clear();
   std::cin.ignore();
   while (true) {
      if (yCord > 0 && yCord <= staticData::fieldSize) {
         break;
      }
      std::cout << "> Invalid entry - try again: ";
      std::cin >> yCord;
      std::cin.clear();
      std::cin.ignore();
   }
   return std::make_tuple(xCord - 1, yCord - 1);
}
