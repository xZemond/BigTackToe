#include "UserInterface.h"

namespace staticData {
   int fieldSize;
   int winSize;
   bool printEnabled;
}

int main()
{
   staticData::fieldSize = 3;
   staticData::winSize = 3;
   staticData::printEnabled = true;
   
   //Initalization
   std::srand(std::time(nullptr));
   std::shared_ptr<Player> player1;
   std::shared_ptr<Player> player2;
   std::shared_ptr<GameControl> game;


   while (true) {
      switch (menu())
      {
      std::system("cls");

      //start Game
      case 1: 
         staticData::printEnabled = true;
         player1 = selectPlayer(Cross);
         player2 = selectPlayer(Circle);
         game = std::make_shared<GameControl>(player1, player2);
         std::system("cls");
         evaluate(game->startGame());  //starts Game and returns Winner
         break;

      //Edit Rules
      case 2:
         editRules();
         break;

      //Test Bots
      case 3:
         staticData::printEnabled = false;
         player1 = selectPlayer(Cross);
         player2 = selectPlayer(Circle);
         testBots(player1, player2);
         break;

      //Exit
      case 4:
         return 69; //nice
      }
   }
}


