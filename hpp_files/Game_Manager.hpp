#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include "Level.hpp"
#include "Player.hpp"
#include "Collectible.hpp"
#include "Gem.hpp"
#include "YellowKey.hpp"
#include "BlueKey.hpp"

/*
=== GameState ===
-> Holds Gamestate on which state the player is right now on.

=== Game_Manager Class ===
-> Accesses Children of GameObject and handles overall game functionality
-> Controls SFML window controls

=== Private Functions ===
-> loadTextures:
-> initUI:
-> initLevel:
-> handleCollisions:
-> handleEvents:
-> update:
-> render:

=== Public Functions ===
->  Game_Manager:
->  ~Game_Manager:
-> run:
-> addScore:
-> addScore:
*/

enum class GameState { WELCOME_MENU, LOADING_SCREEN, HOW_TO_PLAY, PLAYING, LEVEL_COMPLETE, GAME_OVER };

class Game_Manager {
private:
    sf::RenderWindow window;
    GameState currentState;
    GameState nextStateAfterLoading;
    bool musicEnabled;

    sf::Font font;
    sf::Text titleText;
    sf::Text menuText;
    sf::Text howToPlayText;
    sf::Text hudText;
    sf::Text loadingText;

    sf::Clock loadingClock;
    float loadingDuration;

    sf::Texture wallTexture;
    sf::Texture vinesTexture;
    sf::Texture playerTexture;
    sf::Texture snakeTexture;
    sf::Texture rockTexture;
    sf::Texture chestTexture;
    sf::Texture chestOpenTexture;
    sf::Texture gemTexture;
    sf::Texture yellowKeyTexture;
    sf::Texture blueKeyTexture;
    sf::Texture exitDoorClosedTexture;
    sf::Texture exitDoorOpenTexture;

    Player* player;
    Level* currentLevel;

    void loadTextures();
    void initUI();
    void initLevel();
    void handleCollisions();
    void handleEvents();
    void update(float dt);
    void render();

public:
    Game_Manager();
    ~Game_Manager();
    void run();

    void addScore(int points);
    void addScore(const Gem& gem);
};

#endif