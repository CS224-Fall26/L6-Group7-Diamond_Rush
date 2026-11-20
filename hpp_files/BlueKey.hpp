#ifndef BLUE_KEY_HPP
#define BLUE_KEY_HPP

#include "Collectible.hpp"

/*
==== BlueKey Class ===
-> Inherited from collectible
-> Keeps current position and picture
-> picture is rendered on gui using SFML texture feature
*/

class BlueKey : public Collectible {
public:
    BlueKey(Position pos, const sf::Texture& texture);
};

#endif