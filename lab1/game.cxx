#include "game.h"

#include <iostream>

Game::Game() : window("Snake", sf::Vector2u(800, 600)), snake(world.GetBlockSize(), &textbox), world(sf::Vector2u(800, 600))
{
    clock.restart();
    textbox.Setup(5,14,350,sf::Vector2f(225,0));
    srand(time(nullptr));
    elapsed = 0.0f;
    textbox.Add("Seeded random number generator with: " + std::to_string(time(nullptr)));
}

Game::~Game()
{

}

void Game::Render()
{
    window.BeginDraw();

    world.Render(*window.GetRenderWindow());
    snake.Render(*window.GetRenderWindow());
    textbox.Render(*window.GetRenderWindow());
    
    window.EndDraw();
}

Window * Game::GetWindow()
{
    return &window;
}

void Game::HandleInput()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && snake.GetPhysicalDirection() != Direction::Down)
    {
        snake.SetDirection(Direction::Up);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && snake.GetPhysicalDirection() != Direction::Up)
    {
        snake.SetDirection(Direction::Down);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && snake.GetPhysicalDirection() != Direction::Right)
    {
        snake.SetDirection(Direction::Left);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && snake.GetPhysicalDirection() != Direction::Left)
    {
        snake.SetDirection(Direction::Right);
    }
}

void Game::Update()
{
    window.Update();

    float timestep = 1.0f / snake.GetSpeed();

    if(elapsed >= timestep)
    {
        snake.Tick();
        world.Update(snake);
        elapsed -= timestep;

        if(snake.HasLost())
        {
            textbox.Add("GAME OVER! Score: " + std::to_string((long long)snake.GetScore()));
            snake.Reset();
        }
    }
}

sf::Time Game::GetElapsed()
{
    return clock.getElapsedTime();
}

void Game::RestartClock()
{
    elapsed += clock.restart().asSeconds();
}

