#ifndef COLLECTIBLE_HPP
#define COLLECTIBLE_HPP

#include "GameObject.hpp"

/*
=== Collectible Class
-> inherits from GameObject class 
-> Accesses level and position through forward decleration
-> Calls GameObject and store each collectible 
-> Stores collection check (isCollected) and point value for necessary collectible (points)

=== Setters ===
-> collect: update collection check for collectible such that it can be removed from gui
    -> active = false -> check to show that collectible has been collected and can be
    removed from gui
    -> isCollected = true -> collection check for collectible

=== Getters ===
-> getIsCollected: check is collectible has been collected or no
    ->return isCollected
*/

class Collectible : public GameObject {
protected:
    int pointValue;
    bool isCollected;

public:
    Collectible(Position pos, const sf::Texture& texture, int points);
    bool getIsCollected() const;
    void collect();
    
    // Default implementation satisfies the pure virtual requirement from GameObject
    void update(float dt, Level& level) override {}
};

#endif