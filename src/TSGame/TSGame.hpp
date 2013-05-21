#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <memory>
#pragma once
#include <cmath>
#include <Thor/Graphics.hpp>
#include <Thor/Shapes.hpp>
#include <Thor/Particles.hpp>
#include <Thor/Math.hpp>
#include "Particles/Particles.hpp"
#include "Enemy/Enemy.hpp"
#include "Utils/Utils.hpp"

class TSGame
{
private:
    sf::Clock gameClock, levelClock, scoreClock;
    unsigned int level, levelCounter;
    Particles stars;
    float Score, playerSize;
    enemyAI enemyAISine, enemyAILine;
    sf::RenderWindow mainWindow;
    sf::Font mainFont;
    sf::Text textOverlay;
    sf::CircleShape player;
    std::vector<std::unique_ptr<Enemy>> Enemies;
    sf::Color enemyColor;
    sf::Music mainMusic;
    int fpsLimit;
    bool gameStatus;
    menuSystem gameMenu;
    void handleEvents();
    void displayMenu();
    void displayGame();

public:
    void run();
    TSGame();
};

