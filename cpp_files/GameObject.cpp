// GameObject.cpp
#include "GameObject.hpp"


int GameObject::objectCount = 0;

GameObject::GameObject(Position pos, const sf::Texture& texture)
    : position(pos), sprite(texture), active(true) {
    objectCount++;
    sprite.setPosition(sf::Vector2f(static_cast<float>(pos.x * 40), static_cast<float>(pos.y * 40)));
    auto texSize = texture.getSize();
    if (texSize.x > 0 && texSize.y > 0) {
        sprite.setScale({40.f / static_cast<float>(texSize.x), 40.f / static_cast<float>(texSize.y)});
    }
}

GameObject::~GameObject() {
    objectCount--;
}

void GameObject::render(sf::RenderWindow& window) {
    if (active) {
        window.draw(sprite);
    }
}

sf::FloatRect GameObject::getBounds() const {
    return sprite.getGlobalBounds();
}

bool GameObject::isActive() const { return active; }
void GameObject::setActive(bool status) { active = status; }

Position GameObject::getPosition() const { return position; }

void GameObject::setPosition(Position pos) {
    position = pos;
    sprite.setPosition(sf::Vector2f(static_cast<float>(pos.x * 40), static_cast<float>(pos.y * 40)));
}

int GameObject::getObjectCount() { return objectCount; }