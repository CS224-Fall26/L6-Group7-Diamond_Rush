#include "Enemy.hpp"
#include "Level.hpp"

Enemy::Enemy(Position pos, const sf::Texture& texture, int initialDirection)
    : GameObject(pos, texture), moveTimer(0.f), direction(initialDirection) {}

int Enemy::getDirection() const {
    return direction;
}

void Enemy::setDirection(int dir) {
    direction = (dir >= 0) ? 1 : -1;
}