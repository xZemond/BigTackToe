#include "Player.h"


Player::Player(Color color)
: m_color(color) {
}

Player::~Player(){
}

Color Player::getColor() const {
   return m_color;
}

void Player::setField(std::shared_ptr<Field> field) {
   m_field = field;
}
