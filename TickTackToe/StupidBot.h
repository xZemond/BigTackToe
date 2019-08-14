#pragma once
#include "Player.h"
#include "CheckWin.h"

class StupidBot : public Player
{
public:
   StupidBot(Color color);
   ~StupidBot();
   std::tuple<int, int> move() const override;
};

