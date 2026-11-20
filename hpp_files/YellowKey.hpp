#ifndef YELLOW_KEY_HPP
#define YELLOW_KEY_HPP

#include "Collectible.hpp"

/*
==== YellowKey Class ===
-> Inherited from collectible
-> Keeps current position and picture
-> picture is rendered on gui using SFML texture feature
*/

class YellowKey : public Collectible {
public:
    YellowKey(Position pos, const sf::Texture& texture);
};

#endif