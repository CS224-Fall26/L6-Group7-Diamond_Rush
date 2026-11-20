#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"
#include <string>

/*
=======> Player Class <======
=== Relationship ===
-> is-a relation with GameObject
-> Accesses position and Obstacle class through inhertence of GameObject
-> 

=== Constructor ===
-> Player Constructor: To initialize Player

=== Getters ===
-> getName: Return name of the player (string)
-> getLives: Get current number of Lives (int)
-> getGemsCollected: Return Total Number of gems collected (int)
-> getHasYellowKey: Return for true or false when checking collision detection with chests
-> getHasBlueKey: Return for true or false when checking collision detection with Exitdoor

=== Setters ===
-> loseLife: decrement number of lives should player get killed.
-> setHasYellowKey: change status of hasYellowKey (Upon collecting a yellow key in maze) 
to true to collect gems from chest
-> setHasBlueKey: change status of hasBlueKey (Upon collecting a Blue key in maze) 
to true to fullfill one requirement to finish level.

=== Fun Facts by Group 7 ===
-> Q. Why are pixel values in float?
-> Ans. To match sf::Vector2F (2D float value type):
-> Each Picture is 40x40 pixels big
*/ 

class Level;

class Player : public GameObject {
private:
    std::string name;
    int lives;
    int gemsCollected;
    bool hasYellowKey;
    bool hasBlueKey;

public:
    Player(std::string playerName, Position startPos, const sf::Texture& texture);

    std::string getName() const;
    
    int getLives() const;
    void loseLife();

    int getGemsCollected() const;
    void addGem();

    bool getHasYellowKey() const;
    void setHasYellowKey(bool val);

    bool getHasBlueKey() const;
    void setHasBlueKey(bool val);

    void move(int deltaX, int deltaY, Level& level);

    void update(float dt, Level& level) override {}
};

#endif