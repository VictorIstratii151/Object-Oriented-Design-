#include "snake.h"
#include <iostream>

Snake::Snake(int blockSize, Textbox * textbox)
{
    log = textbox;
    size = blockSize;
    bodyRect.setSize(sf::Vector2f(size - 1, size - 1));
    Reset();
}

Snake::~Snake()
{

}

void Snake::Reset()
{
    snakeBody.clear();

    snakeBody.push_back(SnakeSegment(5, 7));
    snakeBody.push_back(SnakeSegment(5, 6));
    snakeBody.push_back(SnakeSegment(5, 5));

    SetDirection(Direction::None);
    speed = 15;
    lives = 3;
    score = 0;
    lost = false;
}

void Snake::SetDirection(Direction dir)
{
    this->dir = dir;
}

Direction Snake::GetDirection() const
{
    return dir;
}

int Snake::GetSpeed() const
{
    return speed;
}

sf::Vector2i Snake::GetPosition() const
{
    return (!snakeBody.empty() ? snakeBody.front().position : sf::Vector2i(1,1));
}

int Snake::GetLives() const
{
    return lives;
}

int Snake::GetScore() const
{
    return score;
}

void Snake::IncreaseScore()
{
    score += 10;
    log->Add("You ate an apple. Score: " + std::to_string((long long)score));
}

bool Snake::HasLost() const
{
    return lost;
}

void Snake::Lose()
{
    lost = true;
}

void Snake::ToggleLost()
{
    lost = !lost;
}

void Snake::Extend()
{
    if(!snakeBody.empty())
    {
        SnakeSegment & tail_head = snakeBody[snakeBody.size() - 1];

        if(snakeBody.size() > 1)
        {
            SnakeSegment & tail_bone = snakeBody[snakeBody.size() - 2];

            if(tail_head.position.x == tail_bone.position.x)
            {
                if(tail_head.position.y > tail_bone.position.y)
                {
                    snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
                }
                else
                {
                    snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
                }
            }
            else if(tail_head.position.y == tail_bone.position.y)
            {
                if(tail_head.position.x > tail_bone.position.x)
                {
                    snakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
                }
                else
                {
                    snakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
                }
            }
            else
            {
                if(dir == Direction::Up)
                {
                    snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
                }
                else if(dir == Direction::Down)
                {
                    snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
                }
                else if(dir == Direction::Left)
                {
                    snakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
                }
                else if(dir == Direction::Right)
                {
                    snakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
                }
            }
        }
    }
    else
    {
        std::cout << "The body is empty lol" << std::endl;
    }
}

void Snake::Tick()
{
    if(!(snakeBody.empty()) && !(dir == Direction::None))
    {
        Move();
        CheckCollision();
    }
}

void Snake::Move()
{
    for(int i = snakeBody.size() - 1; i > 0; --i)
    {
        snakeBody[i].position = snakeBody[i - 1].position;
    }

    if(dir == Direction::Left)
    {
        --snakeBody[0].position.x;
    }
    else if(dir == Direction::Right)
    {
        ++snakeBody[0].position.x;
    }
    else if(dir == Direction::Up)
    {
        --snakeBody[0].position.y;
    }
    else if(dir == Direction::Down)
    {
        ++snakeBody[0].position.y;
    }
}

void Snake::ComputeCollision()
{
    if(snakeBody.size() >= 5)
    {
        SnakeSegment & head = snakeBody.front();
        for(auto itr = snakeBody.begin() + 1; itr != snakeBody.end(); ++itr)
        {
            if(itr->position == head.position)
            {
                int segments = snakeBody.end() - itr;
                Cut(segments);
                break;
            }
        }
    }
}

void Snake::Cut(int segments)
{
    for(int i = 0; i < segments; ++i)
    {
        snakeBody.pop_back();
    }
    --lives;
    if(!lives)
    {
        Lose();
    }

    log->Add("You have lost a life! Lives left: " + std::to_string((long long)lives));
}

void Snake::Render(sf::RenderWindow & window)
{
    if(!snakeBody.empty())
    {
        auto head = snakeBody.begin();

        bodyRect.setFillColor(sf::Color::Yellow);
        bodyRect.setPosition(head->position.x * size, head->position.y * size);

        window.draw(bodyRect);

        bodyRect.setFillColor(sf::Color::Green);
        for(auto itr = snakeBody.begin() + 1; itr != snakeBody.end(); ++itr)
        {
            bodyRect.setPosition(itr->position.x * size, itr->position.y * size);
            window.draw(bodyRect);
        }
    }
}

Direction Snake::GetPhysicalDirection()
{
    if(snakeBody.size() <= 1)
    {
        return Direction::None;
    }

    SnakeSegment& head = snakeBody[0];
    SnakeSegment& neck = snakeBody[1];

    if(head.position.x == neck.position.x)
    {
        return (head.position.y > neck.position.y ? Direction::Down : Direction::Up);
    }
    else if(head.position.y == neck.position.y)
    {
        return (head.position.x > neck.position.x ? Direction::Right : Direction::Left);
    }

    return Direction::None;
}
