#include "Obstacle.hpp"
#include "Level.hpp"
#include "Snake.hpp"
#include "Player.hpp"


Obstacle::Obstacle(Position pos, const sf::Texture& texture, bool isSolid) 
    : GameObject(pos, texture), solid(isSolid) {}

bool Obstacle::isSolid() const { return solid; }


Stone::Stone(Position pos, const sf::Texture& texture) 
    : Obstacle(pos, texture, false), fallTimer(0.f) {}

void Stone::update(float dt, Level& level) {
    if (!active) return;
    fallTimer += dt;
    if (fallTimer > 0.4f) {
        fallTimer = 0.f;
        int targetY = position.y + 1;
        
        if (targetY < level.getHeight() && level.isWalkable(position.x, targetY)) {
            bool blocked = false;
            Snake* targetSnake = nullptr;
            bool hitsPlayer = false;

            for (GameObject* obj : level.getObjects()) {
                if (obj && obj->isActive()) {
                    if (obj->getPosition().x == position.x && obj->getPosition().y == targetY) {
                        // -> Checks if stone landed on a wall or a snake
                        if (Snake* s = dynamic_cast<Snake*>(obj)) {
                            targetSnake = s;
                        } else {
                            blocked = true;
                            break;
                        }
                    }
                }
            }
            // -> to check if rock fell on player
            Player* plyr = level.getPlayer();
            if (plyr && plyr->getPosition().x == position.x && plyr->getPosition().y == targetY) {
                // -> Check pixel-level height difference to ensure stone has fallen from above, 
                // -> rather than just sitting 1 grid cell (40px) right above the player's head.
                float stonePixelY = static_cast<float>(position.y * 40);
                float playerPixelY = static_cast<float>(plyr->getPosition().y * 40);
                float pixelHeightDifference = playerPixelY - stonePixelY;

                // -> Require a larger gap/drop (e.g., > 50 pixels, meaning a 2+ tile drop) 
                // -> so the player can safely stand under a stone at adjacent 40px without instant death.
                if (pixelHeightDifference > 50.f) {
                    hitsPlayer = true;
                } else {
                    blocked = true; // -> Block stone fall if it's resting right above player's head
                }
            }

            if (!blocked) {
                /*
                -> if snake got caught in collision with stone, then delete snake from the gui
                -> else if player got caught, then decrement number of lives
                */
                if (targetSnake) {
                    targetSnake->setActive(false);
                }
                if (hitsPlayer) {
                    if (plyr) {
                        plyr->loseLife();
                        if (plyr->getLives() > 0) {
                            plyr->setPosition(Position(1, 1));
                        }
                    }
                }
                position.y = targetY;
                sprite.setPosition(sf::Vector2f(static_cast<float>(position.x * 40), static_cast<float>(position.y * 40)));
            }
        }
    }
}

bool Stone::push(int dx, Level& level) {
    int targetX = position.x + dx;
    if (level.isWalkable(targetX, position.y)) {
        bool blocked = false;
        for (GameObject* obj : level.getObjects()) {
            /* 
            -> Checks if there is anything in the direction the stone is being pushed 
                -> if yes, then prevent stone from moving
                -> else let it move
            */
            if (obj && obj->isActive() && obj->getPosition().x == targetX && obj->getPosition().y == position.y) {
                blocked = true;
                break;
            }
        }
        if (level.getPlayer() && level.getPlayer()->getPosition().x == targetX && level.getPlayer()->getPosition().y == position.y) {
            blocked = true;
        }
        if (!blocked) {
            position.x = targetX;
            sprite.setPosition(sf::Vector2f(static_cast<float>(position.x * 40), static_cast<float>(position.y * 40)));
            return true;
        }
    }
    return false;
}

Chest::Chest(Position pos, const sf::Texture& closedTex, const sf::Texture& openTex, std::string reward)
    : Obstacle(pos, closedTex, true), isLocked(true), openTexture(openTex), closedTexture(closedTex), rewardType(reward) {}

bool Chest::getIsLocked() const { return isLocked; }

void Chest::unlock() {
    if (isLocked) {
        isLocked = false;
        sprite.setTexture(openTexture);
        auto texSize = openTexture.getSize();
        if (texSize.x > 0) {
            sprite.setScale({40.f / static_cast<float>(texSize.x), 40.f / static_cast<float>(texSize.y)});
        }
    }
}

void Chest::update(float dt, Level& level) {}