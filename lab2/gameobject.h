#pragma once

#include <SFML/Graphics.hpp>

class GameObject
{
    virtual void Render(sf::RenderWindow & window) = 0;
};