#pragma once
#include "GameControl.h"
#include "Player.h"
#include "Field.h"
#include "Human.h"
#include "RandomBot.h"
#include "StupidBot.h"
#include "SmartBot.h"

int menu();
void editRules();
std::shared_ptr<Player> selectPlayer(Color color);
void evaluate(Color result);
void testBots(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2);
bool isNumber(std::string s);

