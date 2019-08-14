#include "UserInterface.h"
#include <string>

//UI for the menu
int menu() {
   std::system("cls");
   std::string selection;
   std::cout << "**************************************************" << std::endl;
   std::cout << "*-------------------   Menu   -------------------*" << std::endl;
   std::cout << "**************************************************" << std::endl;
   std::cout << "*                                                *" << std::endl;
   std::cout << "*  (1) Start Game (default: 3x3)                 *" << std::endl;
   std::cout << "*  (2) Edit rules                                *" << std::endl;
   std::cout << "*  (3) Test Bots                                 *" << std::endl;
   std::cout << "*  (4) Exit                                      *" << std::endl;
   std::cout << "*                                                *" << std::endl;
   std::cout << "**************************************************" << std::endl;
   std::cout << std::endl;
   std::cin >> selection;
   if(isNumber(selection)) {
      if (std::stoi(selection) >= 1 && std::stoi(selection) <= 4) {
         return std::stoi(selection);
      }
   }
   std::cout << "\n> Error: Invalid Entry - try again\n" << std::endl;
   std::system("pause");
   return menu();
}


//UI for Playerselection
std::shared_ptr<Player> selectPlayer(Color color) {
   std::system("cls");
   std::string selection;
   std::cout << "**************************************************" << std::endl;
   std::cout << "*-------------   Select Player " << color + 1 << "   --------------*" << std::endl;
   std::cout << "**************************************************" << std::endl;
   std::cout << "*                                                *" << std::endl;
   std::cout << "*  (1) Human                                     *" << std::endl;
   std::cout << "*  (2) Stupid Bot                                *" << std::endl;
   std::cout << "*  (3) Random Bot                                *" << std::endl;
   std::cout << "*  (4) Smart  Bot                                *" << std::endl;
   std::cout << "*                                                *" << std::endl;
   std::cout << "**************************************************" << std::endl;
   std::cout << std::endl;
   std::cin >> selection;
   if (isNumber(selection)) {
      switch (std::stoi(selection))
      {
      case 1:
         return std::make_shared<Human>(color);
      case 2:
         return std::make_shared<StupidBot>(color);
      case 3:
         return std::make_shared<RandomBot>(color);
      case 4:
         return std::make_shared<SmartBot>(color);
      default:
         std::cout << "\n> Error: Invalid Entry - try again\n" << std::endl;
         std::system("pause");
      };
   }
   std::cout << "\n> Error: Invalid Entry - try again\n" << std::endl;
   std::system("pause");
   return selectPlayer(color);
}


//UI for editing Rules
void editRules() {
   std::system("cls");
   std::cout << "**************************************************" << std::endl;
   std::cout << "*----------------   Edit Rules   ----------------*" << std::endl;
   std::cout << "**************************************************" << std::endl;

   std::string fieldSize;
   std::cout << std::endl << "> Field Size: ";
   std::cin >> fieldSize;
   if (isNumber(fieldSize)) {
      if (std::stoi(fieldSize) > 1) {
         staticData::fieldSize = std::stoi(fieldSize);
      }
   }
   else {
      std::cout << "\n> Error: Invalid Entry - try again\n" << std::endl;
      std::system("pause");
      editRules();
   }

   std::string winSize;
   std::cout << std::endl << "> Signs in a row to win: ";
   std::cin >> winSize;

   if (isNumber(winSize)) {
      if (std::stoi(winSize) > 1 && std::stoi(winSize) <= staticData::fieldSize) {
         staticData::winSize = std::stoi(winSize);
         return;
      }
   }
   else {
   std::cout << "\n> Error: Invalid Entry - try again\n" << std::endl;
   std::system("pause");
   editRules();
   }
}


//UI for evaluation of the result
void evaluate(Color result) {
   switch (result) {
   case Circle:
      std::cout << std::endl << std::endl;
      std::cout << "**************************************************" << std::endl;
      std::cout << "*--------------   Player 1 won !!! --------------*" << std::endl;
      std::cout << "**************************************************" << std::endl;
      break;

   case Cross:
      std::cout << std::endl << std::endl;
      std::cout << "**************************************************" << std::endl;
      std::cout << "*--------------   Player 2 won !!! --------------*" << std::endl;
      std::cout << "**************************************************" << std::endl;
      break;

   case Blank:
      std::cout << std::endl << std::endl;
      std::cout << "**************************************************" << std::endl;
      std::cout << "*---------   Unfortunatly, noone won :( ---------*" << std::endl;
      std::cout << "**************************************************" << std::endl;
      break;
   }
   std::system("pause");
}


//Iteration tests for the bots + UI
void testBots(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2) {
   std::string _iterations;
   int iterations;
   std::system("cls");
   std::cout << "> Reminder: Many iterations / a really big field will take a long time to process ...\n";
   std::cout << "> Select number of Iterations to test: ";
   std::cin >> _iterations;
   if (isNumber(_iterations)) {
      if (std::stoi(_iterations)  > 1) {
         iterations = std::stoi(_iterations);
      }
      else {
         std::cout << "\n> Error: Invalid Entry - try again\n" << std::endl;
         std::system("pause");
         return testBots(player1, player2);
      }
   }
   else {
      std::cout << "\n> Error: Invalid Entry - try again\n" << std::endl;
      std::system("pause");
      return testBots(player1, player2);
   }

   int wins1 = 0;
   int wins2 = 0;
   int draws = 0;
   std::cout << std::endl << " > Processing ..." << std::endl;
   for (int i = 0; i < iterations; i++) {
      auto game = std::make_shared<GameControl>(player1, player2);
      switch (game->startGame()) {
      case Circle:
         wins1 += 1;
         break;
      case Cross:
         wins2 += 1;
         break;
      case Blank:
         draws += 1;
         break;
      }
      if (i % 100 == 0) {
         std::system("cls");
         std::cout << std::endl << " > Processing ..." << std::endl;
         std::cout << std::endl << " > Status: " << i << " of " << iterations << " Iterations done" << std::endl;
      }
   }
   std::system("cls");
   std::cout << "**************************************************" << std::endl;
   std::cout << "*----------------   Evaluation   ----------------*" << std::endl;
   std::cout << "**************************************************" << std::endl << std::endl;
   std::cout << " > Total Games Played: " << iterations;

   std::cout << " > Player 1 wins: " << wins1 << " (" << (float)(100 * wins1 / iterations) << "% winrate)" << std::endl;
   std::cout << " > Player 2 wins: " << wins2 << " (" << (float)(100 * wins2 / iterations) << "% winrate)" << std::endl;
   std::cout << " > Draws: " << draws << " (" << (100 * draws / iterations) << "% drawrate)" << std::endl << std::endl;
   std::cout << " --- With Draws excluded ---\n";
   std::cout << " > Player 1 wins: " << wins1 << " (" << (float)(100 * wins1 / (iterations - draws)) << "% winrate)" << std::endl;
   std::cout << " > Player 2 wins: " << wins2 << " (" << (float)(100 * wins2 / (iterations - draws)) << "% winrate)" << std::endl;
   std::system("pause");
   return;
}


bool isNumber(std::string string)
{
   for (int i = 0; i < string.length(); i++)
      if (isdigit(string[i]) == false)
         return false;
   return true;
}