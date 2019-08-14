#include "CheckWin.h"


namespace checkWin {
   std::shared_ptr<Field> n_field;
   int n_fieldSize;
   Color n_color;
   std::tuple<int, int> n_position;
   int n_winSize;
}

bool checkWin::all(Color color, std::tuple<int, int> position, std::shared_ptr<Field> field)
{
   n_field = field;
   n_fieldSize = staticData::fieldSize - 1;
   n_color = color;
   n_position = position;
   n_winSize = staticData::winSize;
   if (vertical()) return true;
   if (horizontal()) return true;
   if (rising()) return true;
   if (falling()) return true;
   return false;
}

bool checkWin::vertical()
{
   int winCount = 0;
   {
      for (int i = 0; i <= n_fieldSize; i++) {
         if (n_field->getStone(i, std::get<1>(n_position)) == n_color) {
            winCount += 1;
            if (winCount == n_winSize) {
               return true;
            }
         }
         else {
            winCount = 0;
            //runtime optimization ...
            if (i > std::get<0>(n_position)) break; 
            if (i > staticData::fieldSize - staticData::winSize) break;
         }
      }
   }
   return false;
}

bool checkWin::horizontal()
{
   int winCount = 0;
   {
      for (int i = 0; i <= n_fieldSize; i++) {
         if (n_field->getStone(std::get<0>(n_position), i) == n_color) {
            winCount += 1;
            if (winCount == n_winSize) {
               return true;
            }
         }
         else {
            winCount = 0;
            if (i > std::get<1>(n_position)) break;
            if (i > staticData::fieldSize - staticData::winSize) break;
         }
      }
   }
   return false;
}

bool checkWin::rising()
{
   int winCount = 0;
   int xTmp = std::get<0>(n_position);
   int yTmp = std::get<1>(n_position);
   while (true) {
      if (xTmp <= 0 || yTmp >= n_fieldSize) {
         break;
      }
      xTmp -= 1;
      yTmp += 1;
   }
   while (true) {
      if (n_field->getStone(xTmp, yTmp) == n_color) {
         winCount += 1;
         if (winCount == n_winSize) {
            return true;
         }
      }
      else {
         winCount = 0;
         if (xTmp > std::get<1>(n_position)) break;
         if (xTmp > staticData::fieldSize - staticData::winSize) break;
      }
      if (xTmp >= n_fieldSize || yTmp <= 0) {
         break;
      }
      xTmp += 1;
      yTmp -= 1;
   }
   return false;
}

bool checkWin::falling()
{
   int winCount = 0;
   int xTmp = std::get<0>(n_position);
   int yTmp = std::get<1>(n_position);
   while (true) {
      if (xTmp <= 0 || yTmp <= 0) {
         break;
      }
      xTmp -= 1;
      yTmp -= 1;
   }
   while (true) {
      if (n_field->getStone(xTmp, yTmp) == n_color) {
         winCount += 1;
         if (winCount == n_winSize) {
            return true;
         }
      }
      else {
         winCount = 0;
         if (xTmp > std::get<1>(n_position)) break;
         if (xTmp > staticData::fieldSize - staticData::winSize) break;
      }
      if (xTmp >= n_fieldSize || yTmp >= n_fieldSize) {
         break;
      }
      xTmp += 1;
      yTmp += 1;
   }
   return false;
}
