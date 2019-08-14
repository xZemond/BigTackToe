#pragma once
#include "Field.h"
#include "GameControl.h"
#include "Player.h"
#include "CheckWin.h"
#include "StaticData.h"



class GameControl
{
   std::shared_ptr<Field> m_field;
   std::shared_ptr<Player> m_player[2];
   int m_rounds;
   bool m_printEnabled;

public:
   GameControl(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2);
   //creates Game with existing pattern
   GameControl(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2, std::vector<std::vector<Color>> field);
   ~GameControl();
   Color startGame();
};



