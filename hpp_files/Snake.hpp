#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "Enemy.hpp"

/*
=== Snake Class ===
-> Inherits from Enemy class

=== Constructor ===
-> Snake: Intializes Parent with position, image (texture) and current direction

=== Functionality ===
-> update: renders movement of snake onto gui according to the function if else conditions
*/

class Level;

class Snake : public Enemy {
public:
    Snake(Position pos, const sf::Texture& texture, int patRange = 1);

    void update(float dt, Level& level) override;
};

#endif