// ExitDoor.hpp
#ifndef EXITDOOR_HPP
#define EXITDOOR_HPP

#include "Position.hpp"
#include <SFML/Graphics.hpp>

/*
=== ExitDoor Class ===
-> Class that owns a Position class
-> Stores position of exitdoor, Textures (open and closed pictures), isUnlocked 
boolean (to check if all requirements of doors are fullfilled), and sprite function from SFML

=== Constructor ===
-> ExitDoor: Initializes it's position, default picture (Texture) and isUnlocked bool
and then renders itself on the gui

=== Getters ===
-> getPosition: return ExitDoor position for collision check to end level
-> getIsUnlocked: return bool to see if door is now unlocked

=== Setters ===
-> when player collects the blue key, the door unlocks
    -> swaps texture from closed door to opened door

=== Extra Function ===
-> render: to draw ExitDoor onto gui
*/

class ExitDoor {
private:
    Position position;
    bool isUnlocked;
    sf::Sprite sprite;
    sf::Texture closedTex;
    sf::Texture openTex;

public:
    ExitDoor(Position pos, const sf::Texture& closedTexture, const sf::Texture& openTexture);
    Position getPosition() const;
    bool getIsUnlocked() const;
    void setUnlocked(bool unlocked);
    void render(sf::RenderWindow& window);
};

#endif