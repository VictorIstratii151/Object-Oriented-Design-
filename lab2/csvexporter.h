#pragma once

#include <string>
#include "exporter.h"
#include <iostream>

using namespace std;

class CsvExporter : public Exporter 
{
public:
	bool convertMessage(sf::Text * content)
	{
		cout << "style_id, char_size, string\n" + content->getStyle() + ", " + content->getCharacterSize() + " ," + content->getString();
	}
}