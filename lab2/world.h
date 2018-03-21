#pragma once

#include "snake.h"
#include "gameobject.h"

#include <SFML/Graphics.hpp>

class World : public GameObject
{
public:
    World(sf::Vector2u windSize);
    ~World();
    int GetBlockSize() const;
    void RespawnApple();
    void Update(Snake & player);
    void Render(sf::RenderWindow & window);

private:
    sf::Vector2u windowSize;
    sf::Vector2i item; //apple
    int blockSize;
    sf::CircleShape appleShape;
    sf::RectangleShape bounds[4];
};
