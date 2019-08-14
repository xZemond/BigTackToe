#pragma once
#include <tuple>
#include <vector>
#include <list>
#include <iostream>
#include "StaticData.h"

enum Color {Cross, Circle, Blank};

class Field
{
   std::vector<std::vector <Color> > m_field;
   std::list<std::tuple<int, int>> m_blankList;
public:
   Field();
   //Construktor with existing template for the field
   Field(std::vector < std::vector <Color> > field);
   ~Field();
   std::vector<std::vector <Color> > getField();
   Color getStone(int xCord, int yCord) const;
   std::list<std::tuple<int, int> > getBlankList() const;
   bool setStone(std::tuple<int, int> cords, Color color);
   void printField() const;
};

