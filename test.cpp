#include "pch.h"
#include "Field.cpp"
#include "Player.cpp"
#include "CheckWin.cpp"
#include "GameControl.cpp"
#include "Human.cpp"
#include "StupidBot.cpp"
#include "SmartBot.cpp"
#include "RandomBot.cpp"

namespace staticData {
   extern int fieldSize;
   extern int winSize;
   extern bool printEnabled;
}

namespace staticData {
   int fieldSize;
   int winSize;
   bool printEnabled;
}


void testBots(int fieldSize, int winSize, std::shared_ptr<Player> stupidBot, std::shared_ptr<Player> randomBot, std::shared_ptr<Player> smartBot);


Color _ = Blank;
Color X = Cross;
Color O = Circle;


TEST(TestField, field) {
   staticData::fieldSize = 5;
   {
      std::vector<std::vector<Color>> fieldTemplate{
         { _, _, _, _, _ },
         { _, _, _, _, _ },
         { _, _, _, _, _ },
         { _, _, _, _, _ },
         { _, _, _, _, _ },
      };
      auto field = std::make_shared<Field>();
      EXPECT_EQ(field->getField(), fieldTemplate);
      EXPECT_TRUE(field->setStone(std::make_tuple(3, 4), Cross));
      EXPECT_EQ(field->getStone(3, 4), Cross);
      EXPECT_FALSE(field->setStone(std::make_tuple(3, 4), Circle));
   }
   {
      std::vector<std::vector<Color>> fieldTemplate{
         { _, _, X, X, X },
         { X, X, X, X, X },
         { X, _, X, X, X },
         { X, X, X, X, X },
         { X, X, X, X, X },
      };
      auto field = std::make_shared<Field>(fieldTemplate);
      EXPECT_EQ(field->getField(), fieldTemplate);
      std::list<std::tuple <int, int> > templateList{
         std::make_tuple(0, 0),
         std::make_tuple(1, 0),
         std::make_tuple(1, 2)
      };
      EXPECT_EQ(field->getBlankList(), templateList);
   }
}

TEST(TestCheckWin, checkWin) {
   staticData::fieldSize = 3;
   staticData::winSize = 3;

   //Checks if vertival win is recognized
   {
      std::vector<std::vector<Color>> fieldTemplate{
         { X, _, _ },
         { X, _, _ },
         { X, _, _ },
      };
      auto field = std::make_shared<Field>(fieldTemplate);
      EXPECT_TRUE(checkWin::all(Cross, std::make_tuple(0, 0), field));
   }

   //Checks if horizontal win is recognized
   {
      std::vector<std::vector<Color>> fieldTemplate{
         { X, X, X },
         { _, _, _ },
         { _, _, _ },
      };
      auto field = std::make_shared<Field>(fieldTemplate);
      EXPECT_TRUE(checkWin::all(Cross, std::make_tuple(0, 0), field));
   }

   //Checks if falling win is recognized
   {
      std::vector<std::vector<Color>> fieldTemplate{
         { X, _, _ },
         { _, X, _ },
         { _, _, X },
      };
      auto field = std::make_shared<Field>(fieldTemplate);
      EXPECT_TRUE(checkWin::all(Cross, std::make_tuple(1, 1), field));
   }

   //Checks if rising win is recognized
   {
      std::vector<std::vector<Color>> fieldTemplate{
         { _, _, X },
         { _, X, _ },
         { X, _, _ },
      };
      auto field = std::make_shared<Field>(fieldTemplate);
      EXPECT_TRUE(checkWin::all(Cross, std::make_tuple(0, 2), field));
   }

   //Checks if you can win  the other color in the way
   {
      staticData::fieldSize = 4;
      std::vector<std::vector<Color>> fieldTemplate{
         { X, X, O , X},
         { X, X, _ , X},
         { O, _, O , _},
         { X, X, _ , X},
      };
      auto field = std::make_shared<Field>(fieldTemplate);
      EXPECT_FALSE(checkWin::all(Cross, std::make_tuple(0, 0), field));
   }
}

TEST(TestStupidBot, stupidBot) {
   staticData::fieldSize = 3;
   staticData::winSize = 3;

   //Tests if the stupid Bot moves as wanted
   auto player = std::make_shared<StupidBot>(Cross);
   {
      std::vector<std::vector<Color>> fieldTemplate{
         { _, X, _ },
         { X, _, _ },
         { X, _, _ },
      };
      player->setField(std::make_shared<Field>(fieldTemplate));
      EXPECT_EQ(player->move(), std::make_tuple(0, 0));
   }
   {
      std::vector<std::vector<Color>> fieldTemplate{
         { X, _, _ },
         { _, X, _ },
         { X, _, _ },
      };
      player->setField(std::make_shared<Field>(fieldTemplate));
      EXPECT_EQ(player->move(), std::make_tuple(1, 0));
   }
   {
      std::vector<std::vector<Color>> fieldTemplate{
         { X, X, X },
         { X, _, _ },
         { _, X, X },
      };
      player->setField(std::make_shared<Field>(fieldTemplate));
      EXPECT_EQ(player->move(), std::make_tuple(1, 1));
   }
}

TEST(TestSmartBot, smartBot) {
   staticData::fieldSize = 3;
   staticData::winSize = 3;

   //Checks if the SmartBot moves as wanted (unsure win / prevent loss if possible)
   auto player = std::make_shared<SmartBot>(Cross);
   {
      std::vector<std::vector<Color>> fieldTemplate{
         { X, O, _ },
         { X, O, _ },
         { _, _, _ },
      };
      player->setField(std::make_shared<Field>(fieldTemplate));
      EXPECT_EQ(player->move(), std::make_tuple(2, 0));
   }
   {
      std::vector<std::vector<Color>> fieldTemplate{
         { O, X, _ },
         { _, O, _ },
         { _, _, _ },
      };
      player->setField(std::make_shared<Field>(fieldTemplate));
      EXPECT_EQ(player->move(), std::make_tuple(2, 2));
   }
}

TEST(TestWinRate, smartBot) {
   /* Since its likely to draw at tick tack toe, the draws will be excluded */
   auto stupidBot = std::make_shared<StupidBot>(Circle);
   auto randomBot = std::make_shared<RandomBot>(Circle);
   auto smartBot = std::make_shared<SmartBot>(Cross);

   //tests bots with different settings ...
   testBots(3, 3, stupidBot, randomBot, smartBot);
   testBots(4, 3, stupidBot, randomBot, smartBot);
   testBots(4, 4, stupidBot, randomBot, smartBot);
   testBots(5, 3, stupidBot, randomBot, smartBot);
   testBots(5, 4, stupidBot, randomBot, smartBot);
   testBots(5, 5, stupidBot, randomBot, smartBot);
   testBots(6, 3, stupidBot, randomBot, smartBot);
   testBots(6, 4, stupidBot, randomBot, smartBot);
   testBots(6, 5, stupidBot, randomBot, smartBot);
   testBots(6, 6, stupidBot, randomBot, smartBot);
   // ...

   std::system("pause");
}



void testBots(int fieldSize, int winSize, std::shared_ptr<Player> stupidBot, std::shared_ptr<Player> randomBot, std::shared_ptr<Player> smartBot) {
   staticData::fieldSize = fieldSize;
   staticData::winSize = winSize;

   {
      int wins1 = 0;
      int wins2 = 0;
      int draws = 0;
      for (int i = 0; i < 1000; i++) {
         auto game = std::make_shared<GameControl>(stupidBot, smartBot);
         switch (game->startGame()) {
         case Cross:
            wins1 += 1;
            break;
         case Circle:
            wins2 += 1;
            break;
         case Blank:
            draws += 1;
            break;
         }

      }
      std::cout << "\n> Fieldsize: " << staticData::fieldSize << "  Win Size: " << staticData::winSize << " /w StupidBot, Winrate: " << 100 * wins2 / (1000 - draws) << "% --> OK";
      EXPECT_GT(wins2, 4 * wins1);
   }

   {
      int wins1 = 0;
      int wins2 = 0;
      int draws = 0;
      for (int i = 0; i < 1000; i++) {
         auto game = std::make_shared<GameControl>(randomBot, smartBot);
         switch (game->startGame()) {
         case Cross:
            wins1 += 1;
            break;
         case Circle:
            wins2 += 1;
            break;
         case Blank:
            draws += 1;
            break;
         }
      }      
      std::cout << "\n> Fieldsize: " << staticData::fieldSize << "  Win Size: " << staticData::winSize << " /w RandomBot, Winrate: " << 100 * wins2 / (1000 - draws) << "% --> OK";
      EXPECT_GT(wins2, 4*wins1);
   }
}

