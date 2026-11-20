#include "Game_Manager.hpp"     //Including necessary
#include "Snake.hpp"
#include "Obstacle.hpp"
#include <iostream>

/*
=== Global Variables ===
*/
const float WINDOW_WIDTH = 600.f;
const float WINDOW_HEIGHT = 400.f;

/*
=== GameState ===
-> Holds Gamestate on which state the player is right now on.

=== Game_Manager Class ===
-> Accesses Children of GameObject and handles overall game functionality
-> Controls SFML window controls

=== Private Functions ===
-> loadTextures: using SFML Library to load pictures
-> initUI: using SFML Library to add texts onto gui
-> initLevel: Create maze from the maze layout (hardcoded)
and delete any previous player or level (implementation for multi level to be implemented)
-> handleCollisions: Handle collisions between player and other GameObjects
-> handleEvents: Handle keyboard events and change GameStates
-> update: calls GameObjects like snake and stone for their movement functionality
-> render: Render Level complete and Game Over functionality. Changes Gamestate and
also handles canvas window movement functionality

=== Public Functions ===
->  Game_Manager: Constructor used to intialize intial values
->  ~Game_Manager: Destructor to delete level and player
-> run: handles dt used for movement for snakes and stones
-> addScore: Not implemented yet
*/

Game_Manager::Game_Manager() 
    : window(sf::VideoMode(sf::Vector2u(static_cast<unsigned int>(WINDOW_WIDTH), static_cast<unsigned int>(WINDOW_HEIGHT))), "Diamond Rush - Angkor Wat"),
      currentState(GameState::WELCOME_MENU), nextStateAfterLoading(GameState::PLAYING), musicEnabled(true), 
      titleText(font, "DIAMOND RUSH", 32),
      menuText(font, "1. START GAME\n2. HOW TO PLAY\n3. EXIT", 18),
      howToPlayText(font, "Controls:\nArrow Keys / WASD to Move\nCollect Gems and Keys\nYellow Key: Open Chests\nBlue Key: Open Exit Door\n\n[Backspace] Back to Menu", 14),
      hudText(font, "", 14),
      loadingText(font, "Level is loading...", 24),
      loadingDuration(2.0f),
      player(nullptr), currentLevel(nullptr) {
    window.setFramerateLimit(60);
    loadTextures();
    initUI();
}

Game_Manager::~Game_Manager() {
    delete currentLevel;
    delete player;
}

void Game_Manager::loadTextures() {
    if (!wallTexture.loadFromFile("wall.jpg")) std::cerr << "Failed to load wall.jpg\n";
    if (!vinesTexture.loadFromFile("vines.jpg")) std::cerr << "Failed to load vines.jpg\n";
    if (!playerTexture.loadFromFile("player.jpg")) std::cerr << "Failed to load player.jpg\n";
    if (!snakeTexture.loadFromFile("snake.jpg")) std::cerr << "Failed to load snake.jpg\n";
    if (!rockTexture.loadFromFile("rock.jpg")) std::cerr << "Failed to load rock.jpg\n";
    if (!chestTexture.loadFromFile("chest.jpg")) std::cerr << "Failed to load chest.jpg\n";
    if (!chestOpenTexture.loadFromFile("chest_open.jpg")) std::cerr << "Failed to load chest_open.jpg\n";
    if (!gemTexture.loadFromFile("gems.jpg")) std::cerr << "Failed to load gems.jpg\n";
    if (!yellowKeyTexture.loadFromFile("yellow_key.jpeg")) std::cerr << "Failed to load yellow_key.jpeg\n";
    if (!blueKeyTexture.loadFromFile("blue_key.jpeg")) std::cerr << "Failed to load blue_key.jpeg\n";
    if (!exitDoorClosedTexture.loadFromFile("exit_doorclosed.jpeg")) std::cerr << "Failed to load exit_doorclosed.jpeg\n";
    if (!exitDoorOpenTexture.loadFromFile("exit_dooropen.jpeg")) std::cerr << "Failed to load exit_dooropen.jpeg\n";
}

void Game_Manager::initUI() {
    if (!font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cerr << "Warning: Failed to load system font\n";
    }
    
    titleText.setFillColor(sf::Color::Cyan);
    titleText.setPosition(sf::Vector2f(160.f, 80.f));

    menuText.setFillColor(sf::Color::White);
    menuText.setPosition(sf::Vector2f(210.f, 160.f));

    howToPlayText.setFillColor(sf::Color::White);
    howToPlayText.setPosition(sf::Vector2f(160.f, 120.f));

    hudText.setFillColor(sf::Color::Yellow);
    hudText.setPosition(sf::Vector2f(10.f, 10.f));

    loadingText.setFillColor(sf::Color::Cyan);
    loadingText.setPosition(sf::Vector2f(190.f, 180.f));
}

void Game_Manager::initLevel() {
    delete currentLevel;
    delete player;

    player = new Player("Explorer", Position(1, 1), playerTexture);

    std::vector<std::string> layout = {
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
        "WVVVWWWWWWWWWWWWWWVWWVVVWVVWVWSWVVVVVVWWWWWWWW",
        "WVVVVVVVVWWWWWWWWWVWWVWCWVVWVWVWVVVVVVVWWWWWWW",
        "WVVVVVVVVVVWWWWWWWVWWVWWWVVWVWVWVVVVVVVVWWWWWW",
        "WVVVVVVVVVVVVVVVWWVVVVVVVVVWVSVWWWWVVVVVVWWWWW",
        "WVVVVVVVVVVVVVVVVWVVWWVVVVVWVVVWVVVVVVVVVVVVVW",
        "WVVVVVVVVVVVVVVVVVVGWWVVVVVVVVVWVVVVVVVVVVVVVW",
        "WWWWWWWWWWWWWWVVVVRWWWWVVVVVVVVWVVVVVWWWWWWWWW",
        "WWWWWWWWWWWWWWVVVVRVVVGGVVVVVVVVVVVVVVWWWWWWWW",
        "WVVSVVVVSVVVSVVVVWRVVGGGGVVVVVVVVVVVVVVWWWWWWW",
        "WVVVVVVVVVVVVVVVWWWWWWWWWWWWWWWWWWWVVVVVWWVRVW",
        "WVVVVVVVVVVVVVVVVVVRVVVVVVVGGWWWWWVVVVVVVWVCVW",
        "WVVVVVSVVVSVVVVVVVRRRVVVVVGGGWWWWVVVVVVVVVWWGW",
        "WVVVWWWWWWWWWWWWWRRRRRVVVGGGYWWWWVVVVVVVVVVWGW",
        "WVVVWWWWWWWWWWWWWWWWWWWWWWWWWWWWVVVVVVVVVVVGGW",
        "WVVVWWWWWWWWWWWWWVVWVVWVVVVVVVVVVVVVVVVVVVVWWW",
        "WVVVVVVVWVVVWVVVVVVWVVWVVVVVVVVVVVVVVVVVVVVVWW",
        "WVVVVVVVVVVVWVVVVVVWVVWVVWWWWWWWVVVVVVVVVVVVVW",
        "WVVVVVVVVVVVWVVVVVVWVVWVVWWWWWWWVVVVVVVVVVVVVW",
        "WVVVVVVVVVVVVVVVVVVVVVWVVWWWWWWWVVVVVVVVVVVVVW",
        "WVVVVVVVVVVVVVVVVVVVVVWVVVWVVVVVVVVVVVVVVVVVVW",
        "WWWWWWWWWWWWWWWWWVVVVVWVVVWWWWVVVVVVVVVVVVVVVW",
        "WWWWWWWWWWWWWWWVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVW",
        "WVVSVVVVSVVVVSVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVW",
        "WVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVW",
        "WVRVRVVRVRVVRVRVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVW",
        "WWWVWWWWVWWWWVWWWWWVVVVVVVVVVVVVVVVVVVVVVVVVVW",
        "WWWVWWWWVWWWWVWWWWWVVVVVVVVVVVVVVVVVVVVVVVVVVW",
        "WWWVWVVWVWGGWVWVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVW",
        "WBWVWVWWVWVWWVWVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVW",
        "WVWVWVVWVWVVWVWVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVW",
        "WVWVWVVWVWVVWVWVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVW",
        "WVWVWVVWVWVVWVWVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVW",
        "WVWVWVVWVWVVWVWVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVW",
        "WVVVVVVVVVVVVVWVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVW",
        "WWWVWWWWVWWWWVWVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVW",
        "WWWWWWWWWWWWWWVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVW",
        "WWWWWWWWWWWVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVW",
        "WWWWWWWWVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVW",
        "WWWWWWVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVW",
        "WWWVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVW",
        "WVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVW",
        "WVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVW",
        "WWVVVVVVVVVVVVVVVVVVVVVVVWWWWVVVVVVVVVVVVVVVVW",
        "WWWVVVVVVVVVVVVVVVVVVVVVVWWWWVVVVVVVVVVVVVVVVW",
        "WWWWVVVVVVVVVVVVVVVVVVVVVWWWWVVVVVVVVVVVVVVVWW",
        "WWWWWVVVWWWWWWVVVVVVVVVVVWWWWVVVVWWWWWVVVVVWWW",
        "WWWWWWVVWWWWWWVVVVVVVVVVVWWWWVVVWWWWWWWVVVDWWW",
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
    };

    currentLevel = new Level(1, 10, player, Position(42, 47), layout, exitDoorClosedTexture, exitDoorOpenTexture);

    for (int y = 0; y < currentLevel->getHeight(); ++y) {
        for (int x = 0; x < currentLevel->getWidth(); ++x) {
            char tile = currentLevel->getTile(x, y);
            if (tile == 'S') {
                currentLevel->addObject(new Snake(Position(x, y), snakeTexture, 1));
                currentLevel->setTile(x, y, 'V');
            } else if (tile == 'R') {
                currentLevel->addObject(new Stone(Position(x, y), rockTexture));
                currentLevel->setTile(x, y, 'V');
            } else if (tile == 'G') {
                currentLevel->addObject(new Gem(Position(x, y), gemTexture));
                currentLevel->setTile(x, y, 'V');
            } else if (tile == 'Y') {
                currentLevel->addObject(new YellowKey(Position(x, y), yellowKeyTexture));
                currentLevel->setTile(x, y, 'V');
            } else if (tile == 'B' || tile == 'K') {
                currentLevel->addObject(new BlueKey(Position(x, y), blueKeyTexture));
                currentLevel->setTile(x, y, 'V');
            } else if (tile == 'C') {
                currentLevel->addObject(new Chest(Position(x, y), chestTexture, chestOpenTexture, "Gem"));
            }
        }
    }
}

void Game_Manager::handleCollisions() {
    if (!player || !currentLevel) return;

    Position pPos = player->getPosition();

    for (GameObject* obj : currentLevel->getObjects()) {
        if (obj && obj->isActive()) {
            if (player->getBounds().findIntersection(obj->getBounds()).has_value()) {
                if (Gem* gem = dynamic_cast<Gem*>(obj)) {
                    player->addGem();
                    gem->collect();
                } else if (YellowKey* yKey = dynamic_cast<YellowKey*>(obj)) {
                    player->setHasYellowKey(true);
                    yKey->collect();
                } else if (BlueKey* bKey = dynamic_cast<BlueKey*>(obj)) {
                    player->setHasBlueKey(true);
                    currentLevel->getExitDoor().setUnlocked(true);
                    bKey->collect();
                } else if (Snake* snake = dynamic_cast<Snake*>(obj)) {
                    player->loseLife();
                    if (player->getLives() <= 0) {
                        currentState = GameState::GAME_OVER;
                    } else {
                        player->setPosition(Position(1, 1));
                    }
                } else if (Chest* chest = dynamic_cast<Chest*>(obj)) {
                    if (chest->getIsLocked() && player->getHasYellowKey()) {
                        chest->unlock();
                        for (int i = 0; i < 5; ++i) {
                            player->addGem();
                        }
                    }
                }
            }
        }
    }

    // EXACT EXIT DOOR REQUIREMENT CHECK:
    // 1. Player coordinates match the Exit Door coordinates
    // 2. Player has collected at least 10 gems
    // 3. Player has the blue key
    Position doorPos = currentLevel->getExitDoor().getPosition();
    if (pPos.x == doorPos.x && pPos.y == doorPos.y) {
        if (player->getHasBlueKey() && player->getGemsCollected() >= 10) {
            nextStateAfterLoading = GameState::WELCOME_MENU; // Or GameState::LEVEL_COMPLETE
            loadingClock.restart();
            currentState = GameState::LOADING_SCREEN;
        }
    }
}

void Game_Manager::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        handleEvents();
        update(dt);
        render();
    }
}

void Game_Manager::handleEvents() {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (currentState == GameState::WELCOME_MENU) {
                if (keyPressed->code == sf::Keyboard::Key::Num1) {
                    initLevel();
                    nextStateAfterLoading = GameState::PLAYING;
                    loadingClock.restart();
                    currentState = GameState::LOADING_SCREEN;
                } else if (keyPressed->code == sf::Keyboard::Key::Num2) {
                    currentState = GameState::HOW_TO_PLAY;
                } else if (keyPressed->code == sf::Keyboard::Key::Num3 || keyPressed->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
            } else if (currentState == GameState::HOW_TO_PLAY) {
                if (keyPressed->code == sf::Keyboard::Key::Backspace) {
                    currentState = GameState::WELCOME_MENU;
                }
            } else if (currentState == GameState::PLAYING && player && currentLevel) {
                if (keyPressed->code == sf::Keyboard::Key::Up || keyPressed->code == sf::Keyboard::Key::W) {
                    player->move(0, -1, *currentLevel);
                } else if (keyPressed->code == sf::Keyboard::Key::Down || keyPressed->code == sf::Keyboard::Key::S) {
                    player->move(0, 1, *currentLevel);
                } else if (keyPressed->code == sf::Keyboard::Key::Left || keyPressed->code == sf::Keyboard::Key::A) {
                    player->move(-1, 0, *currentLevel);
                } else if (keyPressed->code == sf::Keyboard::Key::Right || keyPressed->code == sf::Keyboard::Key::D) {
                    player->move(1, 0, *currentLevel);
                } else if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    nextStateAfterLoading = GameState::WELCOME_MENU;
                    loadingClock.restart();
                    currentState = GameState::LOADING_SCREEN;
                }
            } else if (currentState == GameState::GAME_OVER || currentState == GameState::LEVEL_COMPLETE) {
                if (keyPressed->code == sf::Keyboard::Key::Enter) {
                    nextStateAfterLoading = GameState::WELCOME_MENU;
                    loadingClock.restart();
                    currentState = GameState::LOADING_SCREEN;
                }
            }
        }
    }
}

void Game_Manager::update(float dt) {
    if (currentState == GameState::LOADING_SCREEN) {
        if (loadingClock.getElapsedTime().asSeconds() >= loadingDuration) {
            currentState = nextStateAfterLoading;
        }
    } else if (currentState == GameState::PLAYING && currentLevel) {
        for (GameObject* obj : currentLevel->getObjects()) {
            if (obj) {
                obj->update(dt, *currentLevel);
            }
        }
        handleCollisions();
    }
}

void Game_Manager::render() {
    window.clear(sf::Color::Black);

    if (currentState == GameState::LOADING_SCREEN) {
        window.setView(window.getDefaultView());
        window.draw(loadingText);
    } else if (currentState == GameState::WELCOME_MENU) {
        window.draw(titleText);
        window.draw(menuText);
    } else if (currentState == GameState::HOW_TO_PLAY) {
        window.draw(howToPlayText);
    } else if (currentState == GameState::PLAYING) {
        sf::Vector2f camCenter = player ? sf::Vector2f(static_cast<float>(player->getPosition().x * 40 + 20), static_cast<float>(player->getPosition().y * 40 + 20)) : sf::Vector2f(300.f, 200.f);

        if (camCenter.x < WINDOW_WIDTH / 2.f) camCenter.x = WINDOW_WIDTH / 2.f;
        if (camCenter.x > currentLevel->getWidth() * 40 - WINDOW_WIDTH / 2.f) camCenter.x = currentLevel->getWidth() * 40 - WINDOW_WIDTH / 2.f;
        if (camCenter.y < WINDOW_HEIGHT / 2.f) camCenter.y = WINDOW_HEIGHT / 2.f;
        if (camCenter.y > currentLevel->getHeight() * 40 - WINDOW_HEIGHT / 2.f) camCenter.y = currentLevel->getHeight() * 40 - WINDOW_HEIGHT / 2.f;

        sf::View view = window.getDefaultView();
        view.setCenter(camCenter);
        window.setView(view);

        for (int y = 0; y < currentLevel->getHeight(); ++y) {
            for (int x = 0; x < currentLevel->getWidth(); ++x) {
                char tile = currentLevel->getTile(x, y);
                sf::Sprite tileSprite(tile == 'W' ? wallTexture : vinesTexture);
                auto texSize = tileSprite.getTexture().getSize();
                if (texSize.x > 0) {
                    tileSprite.setScale({40.f / static_cast<float>(texSize.x), 40.f / static_cast<float>(texSize.y)});
                }
                tileSprite.setPosition(sf::Vector2f(static_cast<float>(x * 40), static_cast<float>(y * 40)));
                window.draw(tileSprite);
            }
        }

        currentLevel->getExitDoor().render(window);

        for (GameObject* obj : currentLevel->getObjects()) {
            if (obj) {
                obj->render(window);
            }
        }

        if (player) {
            player->render(window);
        }

        window.setView(window.getDefaultView());
        std::string hudStr = "Gems: " + std::to_string(player->getGemsCollected()) + 
                             " / 10 | Y-Key: " + (player->getHasYellowKey() ? "YES" : "NO") + 
                             " | B-Key: " + (player->getHasBlueKey() ? "YES" : "NO") + 
                             " | Lives: " + std::to_string(player->getLives());
        hudText.setString(hudStr);
        window.draw(hudText);
    } else if (GameState::GAME_OVER == currentState) {
        window.setView(window.getDefaultView());
        sf::Text gameOverText(font, "GAME OVER\nPress ENTER to Return", 24);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setPosition(sf::Vector2f(170.f, 170.f));
        window.draw(gameOverText);
    } else if (GameState::LEVEL_COMPLETE == currentState) {
        window.setView(window.getDefaultView());
        sf::Text completeText(font, "LEVEL COMPLETED!\nPress ENTER to Return", 24);
        completeText.setFillColor(sf::Color::Green);
        completeText.setPosition(sf::Vector2f(150.f, 170.f));
        window.draw(completeText);
    }

    window.display();
}

void Game_Manager::addScore(int points) {}
void Game_Manager::addScore(const Gem& gem) {}