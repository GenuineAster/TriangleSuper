#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <cmath>

using enemyAI = std::function<sf::Vector2f(sf::Vector2f, sf::Vector2f&, sf::Vector2f&, sf::Vector2f&, float&, float)>;

constexpr double pi = 3.1415926535897932385;

float getRandomNumber(float min, float max);

template<typename V1>
void normalize(V1 &vector1)
{
    float length(sqrtf(vector1.x * vector1.x + vector1.y * vector1.y));
    vector1 /= length;
}

template<typename V1, typename V2>
V2 transformVector(const V1 &vector1, const float scale = 1.f)
{
    V2 vector2;
    vector2.x = vector1.x * scale;
    vector2.y = vector1.y * scale;
    return vector2;
}

sf::Color incrementColor(sf::Color &color);

bool collides(sf::Vector2f enemyPos, sf::Vector2f point);

struct menuSystem
{
    sf::Text titleText, playText, quitText, scoreText;
    void initialize(sf::RenderWindow &mainWindow, sf::Font &mainFont)
    {
        titleText.setFont(mainFont);
        titleText.setString("Triangle Super");
        titleText.setCharacterSize(72);
        titleText.setPosition(mainWindow.getSize().x/2 - titleText.getGlobalBounds().width/2.f,
                              mainWindow.getSize().y/2 - titleText.getGlobalBounds().height/2.f);

        playText.setFont(mainFont);
        playText.setString("Play!");
        playText.setCharacterSize(30);
        playText.setPosition(mainWindow.getSize().x/3 - playText.getGlobalBounds().width/2.f,
                             mainWindow.getSize().y/3 *2 - playText.getGlobalBounds().height/2.f);

        quitText.setFont(mainFont);
        quitText.setString("Quit.");
        quitText.setCharacterSize(30);
        quitText.setPosition(mainWindow.getSize().x/3 *2 - quitText.getGlobalBounds().width/2.f,
                             mainWindow.getSize().y/3*2-quitText.getGlobalBounds().height/2.f);

        scoreText.setFont(mainFont);
        scoreText.setCharacterSize(30);
        scoreText.setPosition(mainWindow.getSize().x/2 - scoreText.getGlobalBounds().width/2.f,
                              mainWindow.getSize().y/3-scoreText.getGlobalBounds().height/2.f);
    }
};
