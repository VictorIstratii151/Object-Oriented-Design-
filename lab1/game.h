#pragma once

#include "window.h"
#include "snake.h"
#include "textbox.h"
#include "world.h"
#include <SFML/Graphics.hpp>

using namespace std;

class Game
{
public:
    Game();
    ~Game();

    void HandleInput();
    void Update();
    void Render();
    Window * GetWindow();
    sf::Time GetElapsed();
    void RestartClock();

private:
    void MoveMushroom();
    Window window;
    Textbox textbox;
    sf::Texture mushroomTexture;
    sf::Sprite mushroom;
    sf::Vector2i increment;
    sf::Clock clock;
    float elapsed;

    World world;
    Snake snake;
};
