#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <cmath>
#include "Utils.hpp"

int getRandomInteger(double min, double max)
{
    double r = (double)rand() / (float)RAND_MAX;
    return min + r * (max - min);
}

sf::Color incrementColor(sf::Color &color)
{
    if(color.a > 254)
    {
        if(color.r > 80)
            color.r--;
        else if(color.g > 80)
            color.g--;
        else if(color.b > 80)
            color.b--;
        else
            color.a--;
    }
    else
    {
        if(color.r < 255)
            color.r++;
        else if(color.g < 255)
            color.g++;
        else if(color.b < 255)
            color.b++;
        else
            color.a = 255;
    }
    return color;
}

bool collides(sf::Vector2f enemyPos, sf::Vector2f point)
{
    return sf::FloatRect{enemyPos, sf::Vector2f{20,15}}.contains(point);
}
