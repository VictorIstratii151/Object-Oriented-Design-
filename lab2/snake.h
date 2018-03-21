#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "textbox.h"
#include "gameobject.h"

using namespace std;

struct SnakeSegment
{
    SnakeSegment(int x, int y) : position(x, y)
    {

    }

    sf::Vector2i position;
};
 
using SnakeContainer = vector<SnakeSegment>;

enum class Direction{ None, Up, Down, Left, Right };

class Snake : public GameObject
{
public:
    Snake(int blockSize, Textbox * textbox);
    ~Snake();

    void SetDirection(Direction dir);
    Direction GetDirection() const;
    Direction GetPhysicalDirection();
    sf::Vector2i GetPosition() const;
    int GetSpeed() const;
    int GetLives() const;
    int GetScore() const;
    void IncreaseScore();
    bool HasLost() const;

    void Lose();
    void ToggleLost();

    void Extend();
    void Reset();

    void Move();
    void Tick();
    void Cut(int segments);
    void Render(sf::RenderWindow & window);

private:
    void ComputeCollision();

    SnakeContainer snakeBody;
    Direction dir;
    int size;
    int speed;
    int lives;
    int score;
    bool lost;
    sf::RectangleShape bodyRect;
    Textbox * log;
};

