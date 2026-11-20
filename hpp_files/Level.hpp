#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "Player.hpp"
#include "GameObject.hpp"
#include "ExitDoor.hpp"

/*
=== Level Class ===
-> Holds GameObject pointer to access it's derived classes.
-> also holds composition relation with ExitDoor and pointer pointing to Player to check
it coordinated whenever needed.

=== Constructor ===
-> Level: initializes it's variables and intializes other classes (ExitDoor and Player)
-> ~Level: Delete GameObjects

=== Setters ===
-> addObject: add another GameObject class to the objects container to keep track of all GameObject's
children in the game
-> setTile: sets it's layout maze with the Tile Letter
    -> W: Wall, S:Snake, R:Stone, V:Vines, etc

=== Getters ===
-> getObjects: return the vector container of objects 
-> getPlayer: return player pointer used for collision check
-> isWalkable (overloaded function): One with x, y parameters and one with pos parameter:
    -> evidently return a bool to check if the new path, the GameObject's child needs to 
    is valid or no
-> getWidth: return width of maze layout (use ternary operators "?")
-> getHeight: return height of maze layout (use ternary operators "?")
-> checkCompletion: check if player fullfills requirements to complete and finish level
-> getExitDoor: return address of ExitDoor class to check collision
*/

class Level {
private:
    int levelNumber;
    int gemGoal;
    bool isComplete;
    std::vector<GameObject*> objects;
    Player* player;
    ExitDoor exitDoor;
    std::vector<std::string> layout;

public:
    Level(int num, int goal, Player* plyr, Position exitPos, const std::vector<std::string>& mapLayout, const sf::Texture& closedTex, const sf::Texture& openTex);
    ~Level();

    void addObject(GameObject* obj);
    const std::vector<GameObject*>& getObjects() const;
    Player* getPlayer() const;

    bool isWalkable(Position pos) const;
    bool isWalkable(int x, int y) const;

    char getTile(int x, int y) const;
    void setTile(int x, int y, char tile);

    int getWidth() const;
    int getHeight() const;

    bool checkCompletion();
    ExitDoor& getExitDoor();
};

#endif