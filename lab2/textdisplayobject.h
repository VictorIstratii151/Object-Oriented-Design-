#pragma once

#include "gameobject.h"

#include <string>

class TextDisplayObject : public GameObject
{
    virtual void Setup(int visible, int charSize, int width, sf::Vector2f screenPos) = 0;
    virtual void Add(std::string message) = 0;
    virtual void Clear() = 0;
};