// GameObject.hpp
#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>
#include "Position.hpp"

/*
=== Game Object Class ===
-> Parent Abstract Class

=== Static Variables ===
-> Used to keep count of the Number of GameObjects in the game

=== Constructor ===
-> GameObject: Initializes it's variables when GameObjects are made and increment count
-> ~GameObject: Delete Child Objects and itself. And also decrement objectCount

=== Functionality
-> render: Checks if GameObject is active, then render it onto gui

=== Getters ===
-> getBounds: return boundary coordinates of GameObject children
-> isActive: return active status of child
-> getPosition: return maze coordinates of GameObject child
-> getObjectCount: return total number of children created

=== Setters ===
-> setActive: change active status of child
-> setPosition: set position GameObject child on gui through the Vector2F from SFML

-> Forward Decleration of Level as it is Used in the virtual function.
*/

class Level; // Forward declaration

class GameObject {
protected:
    Position position;
    sf::Sprite sprite;
    bool active;
    static int objectCount;

public:
    GameObject(Position pos, const sf::Texture& texture);
    virtual ~GameObject();

    virtual void update(float dt, Level& level) = 0;
    virtual void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
    bool isActive() const;
    void setActive(bool status);
    Position getPosition() const;
    void setPosition(Position pos);
    
    static int getObjectCount();
};

#endif