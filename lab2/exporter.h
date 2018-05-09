#pragma once

#include <SFML/Graphics.hpp>

class Exporter
{
public:
	virtual bool convertMessage(sf::Text * content;) = 0;
}