#pragma once
#include <tuple>
#include <algorithm>
#include <iterator>
#include "Field.h"
#include "StaticData.h"

class Player
{
protected:
   Color m_color;
   std::shared_ptr<Field> m_field;
public:
   Player(Color color);
   ~Player();
   virtual std::tuple<int, int> move() const = 0;
   Color getColor() const;
   void setField(std::shared_ptr<Field> field);
};

