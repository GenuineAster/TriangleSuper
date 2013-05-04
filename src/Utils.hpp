#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <cmath>

#ifdef _WIN32
#define M_PI 3.14159
#endif

int getRandomInteger(double min, double max);

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
