#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "GameObject.hpp"

/*
=== Enemy Class ===
-> Inherits from GameObject

=== Constructor ===
-> Initializes GameObject with position of Enemy once.
-> set direction of Enemy with their intial direction.

=== Getters ===
-> getDirection: Not yet used -> TO BE IMPLEMENTED FOR BOSS

=== Setters ===
-> setDirection: TO BE IMPLEMTNED FOR BOSS AND NEW TYPES OF SNAKES
*/

class Level;

class Enemy : public GameObject {
protected:
    float moveTimer;
    int direction;

public:
    Enemy(Position pos, const sf::Texture& texture, int initialDirection = 1);
    // Tells compiler that it's child classes will get deleted, but the defination of it is not needed
    virtual ~Enemy() = default;

    int getDirection() const;
    void setDirection(int dir);
    // Override = 0, to show that parent function is overriden but not used.
    void update(float dt, Level& level) override = 0;
};

#endif