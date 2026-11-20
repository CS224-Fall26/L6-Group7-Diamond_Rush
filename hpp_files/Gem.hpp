#ifndef GEM_HPP
#define GEM_HPP

#include "Collectible.hpp"
#include <string>

/*
==== Gem Class ===
-> Gem inherits from collectible
-> stores current position and points
-> points right now not being used as there is only one gem therefore scoring not
necessary
*/

class Gem : public Collectible {
    public:
        Gem(Position pos, const sf::Texture& texture, int points = 100);
};

#endif