#pragma once
#include <ctime>
#include "Player.h"

class RandomBot : public Player
{
public:
   RandomBot(Color color);
   ~RandomBot();
   std::tuple<int, int> move() const override;
};

