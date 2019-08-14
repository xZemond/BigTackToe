#pragma once
#include <ctype.h>
#include <iostream>
#include "Player.h"

class Human : public Player
{
public:
   Human(Color color);
   ~Human();
   std::tuple<int, int> move() const override;
};

