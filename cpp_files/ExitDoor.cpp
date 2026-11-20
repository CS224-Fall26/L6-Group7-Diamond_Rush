// ExitDoor.cpp
#include "ExitDoor.hpp"

ExitDoor::ExitDoor(Position pos, const sf::Texture& closedTexture, const sf::Texture& openTexture) 
    : position(pos), isUnlocked(false), closedTex(closedTexture), openTex(openTexture), sprite(closedTexture) {
    sprite.setPosition(sf::Vector2f(static_cast<float>(pos.x * 40), static_cast<float>(pos.y * 40)));
    auto texSize = closedTexture.getSize();
    if (texSize.x > 0) {
        sprite.setScale({40.f / static_cast<float>(texSize.x), 40.f / static_cast<float>(texSize.y)});
    }
}

Position ExitDoor::getPosition() const { return position; }
bool ExitDoor::getIsUnlocked() const { return isUnlocked; }

void ExitDoor::setUnlocked(bool unlocked) {
    isUnlocked = unlocked;
    if (isUnlocked) {
        sprite.setTexture(openTex);
    } else {
        sprite.setTexture(closedTex);
    }
    auto texSize = sprite.getTexture().getSize();
    if (texSize.x > 0) {
        sprite.setScale({40.f / static_cast<float>(texSize.x), 40.f / static_cast<float>(texSize.y)});
    }
}

void ExitDoor::render(sf::RenderWindow& window) {
    window.draw(sprite);
}