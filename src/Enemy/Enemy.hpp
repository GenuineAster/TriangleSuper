#pragma once
#include <Thor/Graphics.hpp>
#include <Thor/Shapes.hpp>
#include <Thor/Particles.hpp>
#include <Thor/Math.hpp>
#include <SFML/Graphics.hpp>
#include "Particles/Particles.hpp"
#include "Utils/Utils.hpp"
#include <cmath>

class Enemy
{
private:
    Particles particleSystem;
    thor::ConcaveShape shape;
    sf::Vector2f Destination, linearPosition, startingPoint;
    float angle;
    std::function<sf::Vector2f(sf::Vector2f, sf::Vector2f&, sf::Vector2f&, sf::Vector2f&, float&, float&)> algorithm;
public:
    void incrementColor();
    void setColor(sf::Color color);
    const thor::ConcaveShape &getShape();
    void Update(float delaTime);
    void render(sf::RenderWindow &window);
    Enemy(sf::Color color, sf::Vector2f position, sf::Vector2f Destination_, enemyAI algorithm_);
};
