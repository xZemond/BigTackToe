#pragma once
#include "Player.h"
#include "CheckWin.h"

class SmartBot : public Player
{
public:
   SmartBot(Color color);
   ~SmartBot();
   std::tuple<int, int> move() const override;
};

