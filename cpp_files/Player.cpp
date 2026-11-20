#include "Player.hpp"
#include "Level.hpp"
#include "Obstacle.hpp"


Player::Player(std::string playerName, Position startPos, const sf::Texture& texture)
    : GameObject(startPos, texture), name(playerName), lives(3), gemsCollected(0), hasYellowKey(false), hasBlueKey(false) {}

std::string Player::getName() const { return name; }
int Player::getLives() const { return lives; }
void Player::loseLife() { lives--; }

int Player::getGemsCollected() const { return gemsCollected; }
void Player::addGem() { gemsCollected++; }

bool Player::getHasYellowKey() const { return hasYellowKey; }
void Player::setHasYellowKey(bool val) { hasYellowKey = val; }

bool Player::getHasBlueKey() const { return hasBlueKey; }
void Player::setHasBlueKey(bool val) { hasBlueKey = val; }

void Player::move(int deltaX, int deltaY, Level& level) {
    /*
    -> Update Location of Player according to conditions below.
    */
    int targetX = position.x + deltaX;
    int targetY = position.y + deltaY;

    /*
    -> Get's Letter coordinate of Tile (mentioned in Game_Manager initLevel())
    -> Call method of Level: getTile
    -> Checks Attribute hasBlueKey to check for levelcompletion.
    -> The position of player is updated using sprite.setPosition and then level is
    accessed using through it's method checkCompletion.
    -> This helps render the position of the player and also update if levelcompletion
    if player has gems>=10 and a blue key
    */


    char targetTile = level.getTile(targetX, targetY);
    if (targetTile == 'D') {
        if (hasBlueKey) {
            position.x = targetX;
            position.y = targetY;
            sprite.setPosition(sf::Vector2f(static_cast<float>(position.x * 40), static_cast<float>(position.y * 40)));
            level.checkCompletion();
            return;
        } else {
            return; // Blocked if door is locked
        }
    }

    /*
    -> Calls method function isWalkable to check if player can move to the new coordinate on map or no
    -> If condition True:
    1. Iterates over all objects and checks the following:
        -> Is object is active. (if object currently in graph or deleted)
        -> is position of object is same as position of next coordinate of player
        -> if object is a stone, then check if player is moving upwards or downwards
        -> if moving sideways then push stone to the direction player is trying to move.
            -> update stone and player coordinates
        -> else don't allow to move both
    2. Why dynamic cast used?
        -> to check if the object is actually a stone derived class of obj or no
    3. Why static cast used?
        -> to safetly convert int to float for sf::Vector2F
    */
    if (level.isWalkable(targetX, targetY)) {
        bool blockedByStone = false;
        for (GameObject* obj : level.getObjects()) {
            if (obj && obj->isActive() && obj->getPosition().x == targetX && obj->getPosition().y == targetY) {
                if (Stone* stone = dynamic_cast<Stone*>(obj)) {
                    if (deltaY == 0) { // Horizontal push only
                        if (stone->push(deltaX, level)) {
                            position.x = targetX;
                            position.y = targetY;
                            sprite.setPosition(sf::Vector2f(static_cast<float>(position.x * 40), static_cast<float>(position.y * 40)));
                        }
                    }
                    blockedByStone = true;
                    break;
                }
            }
        }
        if (!blockedByStone) {
            position.x = targetX;
            position.y = targetY;
            sprite.setPosition(sf::Vector2f(static_cast<float>(position.x * 40), static_cast<float>(position.y * 40)));
        }
    } 
    /*
    Additional check for stone especially bcz stone can be moved sideways
    ????? CHECK BCZ THIS IS REPEATING CONDIITON
    */
    else {
        if (targetTile == 'R' && deltaY == 0) {
            for (GameObject* obj : level.getObjects()) {
                if (obj && obj->isActive() && obj->getPosition().x == targetX && obj->getPosition().y == targetY) {
                    Stone* stone = dynamic_cast<Stone*>(obj);
                    if (stone && stone->push(deltaX, level)) {
                        position.x = targetX;
                        position.y = targetY;
                        sprite.setPosition(sf::Vector2f(static_cast<float>(position.x * 40), static_cast<float>(position.y * 40)));
                    }
                    break;
                }
            }
        }
    }
}

/* === REPLACE THIS WITH ORIGINAL LATER ====
void Player::move(int deltaX, int deltaY, Level& level) {
    int targetX = position.x + deltaX;
    int targetY = position.y + deltaY;

    char targetTile = level.getTile(targetX, targetY);
    if (targetTile == 'D') {
        if (hasBlueKey) {
            position.x = targetX;
            position.y = targetY;
            sprite.setPosition(sf::Vector2f(static_cast<float>(position.x * 40), static_cast<float>(position.y * 40)));
            level.checkCompletion();
        }
        return;
    }

    Stone* stoneAtTarget = nullptr;
    for (GameObject* obj : level.getObjects()) {
        if (obj && obj->isActive() && obj->getPosition() == Position(targetX, targetY)) {
            if (Stone* stone = dynamic_cast<Stone*>(obj)) {
                stoneAtTarget = stone;
                break;
            }
        }
    }

    if (stoneAtTarget != nullptr) {
        if (deltaY == 0 && stoneAtTarget->push(deltaX, level)) {
            position.x = targetX;
            position.y = targetY;
            sprite.setPosition(sf::Vector2f(static_cast<float>(position.x * 40), static_cast<float>(position.y * 40)));
        }
        return;
    }

    if (level.isWalkable(targetX, targetY)) {
        position.x = targetX;
        position.y = targetY;
        sprite.setPosition(sf::Vector2f(static_cast<float>(position.x * 40), static_cast<float>(position.y * 40)));
    }
}
*/