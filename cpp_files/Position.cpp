// Position.cpp
#include "Position.hpp"

Position::Position(int px, int py) : x(px), y(py) {}

bool Position::operator==(const Position& other) const {
    return (x == other.x && y == other.y);
}