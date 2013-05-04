#include <Thor/Graphics.hpp>
#include <Thor/Shapes.hpp>
#include <Thor/Particles.hpp>
#include <Thor/Math.hpp>
#include <SFML/Graphics.hpp>
#include "Enemy.hpp"
#include "Utils.hpp"


void Enemy::setColor(sf::Color color)
{
    shape.setFillColor(color);
    color.r -= 60;
    color.g -= 60;
    color.b -= 60;
    particleSystem.setColor(color);
}

const thor::ConcaveShape &Enemy::getShape()
{
    return shape;
}

void Enemy::Update(float delaTime)
{
    shape.setPosition(algorithm(shape.getPosition(), startingPoint, Destination, linearPosition, angle, delaTime));
    particleSystem.setPosition(shape.getPosition());
    particleSystem.Update();
}

void Enemy::render(sf::RenderWindow &window)
{
    window.draw(particleSystem.getSystem());
    window.draw(shape);
}

Enemy::Enemy(sf::Color color, sf::Vector2f position, sf::Vector2f Destination_,
             std::function<sf::Vector2f(sf::Vector2f, sf::Vector2f&, sf::Vector2f&, sf::Vector2f&, float&, float&)> algorithm_) :
    particleSystem(sf::Color(color.r-100, color.b-100, color.g-100, color.a), 4, 10, sf::Vector2f(0.5f,0.5f), sf::Vector2i(0,3),
                   position, 5.f, sf::Vector2f(5.f,5.f), 5.f, sf::Vector2f(0.f, 360.f))
{
    Destination = Destination_;
    algorithm = algorithm_;
    startingPoint = position;
    linearPosition = position;
    shape.setPointCount(4);
    shape.setPoint(0, sf::Vector2f(0,0));
    shape.setPoint(1, sf::Vector2f(10,5));
    shape.setPoint(2, sf::Vector2f(20,0));
    shape.setPoint(3, sf::Vector2f(10,15));
    shape.setFillColor(color);
    shape.setOrigin(10,5);
    shape.setPosition(position);
    sf::Vector2f direction {Destination - position};
    normalize(direction);
    (direction.x > 0) ? (shape.rotate(std::atan(direction.y / direction.x) * 180 / M_PI - 90)) : (shape.rotate(std::atan(direction.y / direction.x) * 180 / M_PI - 270));
}
