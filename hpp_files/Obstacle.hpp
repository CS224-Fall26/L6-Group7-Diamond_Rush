#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "GameObject.hpp"
#include <string>

/*
=== Obstacle Class ===
-> Inherits from GameObject and has Derived Classes (Stone and Chest)

=== Constructor ===
-> Initalized and stores, current Obstacle's position, picture (Texture) and if
the Obstacle is movable or not (isSolid)

=== Getters ===
-> isSolid: returns bool if the Obstacle (stone or chest) is movable or not
*/

class Level;

class Obstacle : public GameObject {
protected:
    bool solid;

public:
    Obstacle(Position pos, const sf::Texture& texture, bool isSolid);
    bool isSolid() const;
};

/*
=== Stone Class ===
-> Inherits from Obstacle
-> fall timer: After how many seconds will it fall 40 pixels down

=== Constructor ===
-> Stone: Initializes Obstacle with it's current position, Picture(Texture) and falltimer.
-> For Stone, isSolid is false by default

=== Functionality ===
1. update: fall functionality of stone + collision functionality with snake and player
2. push: 
*/

class Stone : public Obstacle {
private:
    float fallTimer;

public:
    Stone(Position pos, const sf::Texture& texture);
    void update(float dt, Level& level) override;
    bool push(int dx, Level& level);
};

/*
=== Chest Class ===
-> Inherits from Obstacle

=== Constructor ===
-> Chest: Initializes with position, Closed chest pic and open chest pic (Texture), rewards and 
locked boolean (isLocked)

=== Getters ===
-> getIsLocked: return bool is chest is locked or has been opened by player

=== Functionality ===
-> unlock: if player has acquired yellowkey, then chest is unlocked. 
    -> swap closed chest picture with open chest picture
-> update: used to override grandparent's virtual function (update function)
*/

class Chest : public Obstacle {
private:
    bool isLocked;
    sf::Texture openTexture;
    sf::Texture closedTexture;
    std::string rewardType;

public:
    Chest(Position pos, const sf::Texture& closedTex, const sf::Texture& openTex, std::string reward);
    bool getIsLocked() const;
    void unlock();
    void update(float dt, Level& level) override;
};

#endif