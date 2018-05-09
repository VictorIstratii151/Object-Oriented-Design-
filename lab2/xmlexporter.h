#pragma once

#include <string>
#include "exporter.h"
#include <iostream>

using namespace std;

class XmlExporter : public Exporter 
{
public:
	bool convertMessage(sf::Text * content)
	{
		cout << "<message>\n	<charsize>\n" + "		" + content->getCharacterSize() + "\n</charsie>\n" + "</message>\n";
	}
}