#pragma once

#include <SFML/Graphics.hpp>

using namespace std;

class Window
{
public:
    Window();
    Window(const string& title, const sf::Vector2u& size);
    ~Window();

    void BeginDraw();
    void EndDraw();

    void Update();

    bool IsDone();
    bool IsFullScreen();
    sf::RenderWindow * GetRenderWindow();
    sf::Vector2u GetWindowSize();

    void ToggleFullscreen();

    void Draw(sf::Drawable& drawable);

private:
    void Setup(const string& title, const sf::Vector2u& size);
    void Destroy();
    void Create();

    sf::RenderWindow window;
    sf::Vector2u windowSize;
    string windowTitle;
    bool isDone;
    bool isFullScreen;
};
