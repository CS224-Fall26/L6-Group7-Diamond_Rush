// Position.hpp
#ifndef POSITION_HPP
#define POSITION_HPP

/*
=== Position Struct ===
-> attributes are public (by default)
-> contains position x, y coordinates

=== Constructor ===
-> Initialized with 0,0 after which it can be changed to current coordinates

=== Methods ===
-> operator== overloading
    -> Check for collision check for ExitDoor and Player to end level.
*/

struct Position {
    int x;
    int y;

    Position(int px = 0, int py = 0);
    bool operator==(const Position& other) const;
};

#endif