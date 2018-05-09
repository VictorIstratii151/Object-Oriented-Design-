#pragma once

#include "exporter.h"
#include 

class ExportController
{
private:
	Exporter * exporter;

public:
	void setExporter(Exporter * exporter);
	void runExport(sf::Text * content)
	{
		exporter->convertMessage(content);
	}
};