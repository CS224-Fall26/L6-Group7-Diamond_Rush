#include "Collectible.hpp"

Collectible::Collectible(Position pos, const sf::Texture& texture, int points) 
    : GameObject(pos, texture), pointValue(points), isCollected(false) {}

bool Collectible::getIsCollected() const { 
    return isCollected; 
}

void Collectible::collect() { 
    isCollected = true; 
    active = false; 
}