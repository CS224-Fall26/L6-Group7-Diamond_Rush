#include "Snake.hpp"
#include "Level.hpp"

Snake::Snake(Position pos, const sf::Texture& texture, int patRange)
    : Enemy(pos, texture, 1) {}

void Snake::update(float dt, Level& level) {
    // Check if snake is still in the game or deleted
    if (!active) return;

    /*
    -> Movement control of snake:
    -> moveTimer: used as a timer after which the snake moves
    -> targetY is first calculated with direction (inherited from Enemy) 
    -> then we check if snake is getting blocked by any active object in the maze
        -> if yes, then we reverse the direction of snake
        -> if no, then keep going to it's current direction
    
    */
    moveTimer += dt;
    if (moveTimer > 0.6f) {
        moveTimer = 0.f;
        int targetY = position.y + direction;

        bool blockedByObject = false;
        for (GameObject* obj : level.getObjects()) {
            if (obj && obj->isActive() && obj->getPosition().x == position.x && obj->getPosition().y == targetY) {
                blockedByObject = true;
                break;
            }
        }

        if (targetY >= 0 && targetY < level.getHeight() && level.isWalkable(position.x, targetY) && !blockedByObject) {
            position.y = targetY;
            sprite.setPosition(sf::Vector2f(static_cast<float>(position.x * 40), static_cast<float>(position.y * 40)));
        } else {
            direction = -direction;
        }

        /*
        -> Check which direction is snake going in, then change orientation of 
        Snake picture
        */
        sf::Vector2u texSize = sprite.getTexture().getSize();
        if (texSize.x > 0 && texSize.y > 0) {
            /*
            -> static_cast used to convert int to float safetly
            */
            float scaleX = 40.f / static_cast<float>(texSize.x);
            float scaleY = 40.f / static_cast<float>(texSize.y);
            if (direction < 0) {
                sprite.setScale(sf::Vector2f(scaleX, scaleY));
                sprite.setOrigin(sf::Vector2f(0.f, 0.f));
            } else {
                sprite.setScale(sf::Vector2f(scaleX, -scaleY));
                sprite.setOrigin(sf::Vector2f(0.f, static_cast<float>(texSize.y)));
            }
        }
    }
}