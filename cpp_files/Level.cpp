#include "Level.hpp"


Level::Level(int num, int goal, Player* plyr, Position exitPos, const std::vector<std::string>& mapLayout, const sf::Texture& closedTex, const sf::Texture& openTex) 
    : levelNumber(num), gemGoal(goal), isComplete(false), player(plyr), exitDoor(exitPos, closedTex, openTex), layout(mapLayout) {}

Level::~Level() {
    for (GameObject* obj : objects) {
        delete obj;
    }
    objects.clear();
}

void Level::addObject(GameObject* obj) {
    objects.push_back(obj);
}

const std::vector<GameObject*>& Level::getObjects() const {
    return objects;
}

Player* Level::getPlayer() const {
    return player;
}

bool Level::isWalkable(Position pos) const {
    if (pos.x < 0 || pos.y < 0 || pos.y >= static_cast<int>(layout.size()) || pos.x >= static_cast<int>(layout[pos.y].length())) {
        return false;
    }
    char tile = layout[pos.y][pos.x];
    if (tile == 'W') return false;
    if (tile == 'R') return false;
    if (tile == 'D') {
        if (!player || !player->getHasBlueKey()) {
            return false;
        }
    }
    return true;
}

bool Level::isWalkable(int x, int y) const {
    return isWalkable(Position(x, y));
}

char Level::getTile(int x, int y) const {
    if (y >= 0 && y < static_cast<int>(layout.size()) && x >= 0 && x < static_cast<int>(layout[y].length())) {
        return layout[y][x];
    }
    return 'W';
}

void Level::setTile(int x, int y, char tile) {
    if (y >= 0 && y < static_cast<int>(layout.size()) && x >= 0 && x < static_cast<int>(layout[y].length())) {
        layout[y][x] = tile;
    }
}

int Level::getWidth() const {
    return layout.empty() ? 0 : static_cast<int>(layout[0].length());
}

int Level::getHeight() const {
    return static_cast<int>(layout.size());
}

bool Level::checkCompletion() {
    if (player && player->getGemsCollected() >= gemGoal && player->getHasBlueKey()) {
        isComplete = true;
        exitDoor.setUnlocked(true);
    }
    return isComplete;
}

ExitDoor& Level::getExitDoor() {
    return exitDoor;
}