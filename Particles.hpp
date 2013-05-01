#ifndef _PARTICLES_HPP_
#define _PARTICLES_HPP_

#include <Thor/Graphics.hpp>
#include <Thor/Shapes.hpp>
#include <Thor/Particles.hpp>
#include <Thor/Math.hpp>
#include <SFML/Graphics.hpp>

class Particles
{
private:
    sf::Image Image;
    sf::Texture Texture;
    thor::ParticleSystem System;
    sf::Clock Clock;
    thor::UniversalEmitter::Ptr Emitter;
    thor::Affector::Ptr Affector;
    float radius;
public:
    const thor::ParticleSystem &getSystem();
    void setPosition(sf::Vector2f position, float radius_ = -1.f);
    void Update();
    void setColor(sf::Color color);
    Particles(sf::Color color, int particleSize, int rate, sf::Vector2f force, sf::Vector2i timeRange, sf::Vector2f position, float radius_, sf::Vector2f direction, float maxRotation, sf::Vector2f rotation);// : System(Texture);
};
#endif // _PARTICLES_HPP_
