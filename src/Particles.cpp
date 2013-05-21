#include <Thor/Graphics.hpp>
#include <Thor/Shapes.hpp>
#include <Thor/Particles.hpp>
#include <Thor/Math.hpp>
#include <SFML/Graphics.hpp>
#include "Particles.hpp"
#include "Utils.hpp"

const thor::ParticleSystem &Particles::getSystem(){return System;}
void Particles::Update(){System.update(Clock.restart());}
void Particles::setColor(sf::Color color){Image.create(Image.getSize().x, Image.getSize().y, color);}

void Particles::setPosition(sf::Vector2f position, float radius_)
{
    if(radius_ < 0)
        radius_ = radius;
    Emitter->setParticlePosition(thor::Distributions::circle(position, radius_));
}

Particles::Particles(sf::Color color, int particleSize, int rate, sf::Vector2f force, sf::Vector2i timeRange,
                     sf::Vector2f position, float radius_, sf::Vector2f direction, float maxRotation, sf::Vector2f rotation) : System {Texture}
{
    radius = radius_;
    Image.create(particleSize, particleSize, color);
    Texture.loadFromImage(Image);
    Emitter = thor::UniversalEmitter::create();
    Affector = thor::ForceAffector::create(force);
    System.addAffector(Affector);
    Emitter->setEmissionRate(rate);
    Emitter->setParticleLifetime(thor::Distributions::uniform(sf::seconds(timeRange.x), sf::seconds(timeRange.y)));
    Emitter->setParticlePosition(thor::Distributions::circle(position, radius));
    Emitter->setParticleVelocity(thor::Distributions::deflect(direction, maxRotation));
    Emitter->setParticleRotation(thor::Distributions::uniform(rotation.x, rotation.y));
    System.addEmitter(Emitter);
}
