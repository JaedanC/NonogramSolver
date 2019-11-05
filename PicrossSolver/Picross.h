#include <vector>
#include "Row.h"

#pragma once
class Picross {
	int width, height;
	std::vector<Row> allRows;
	short** grid;

public:
	Picross(std::vector<short> dims,
		std::vector<std::vector<short> > columnData,
		std::vector<std::vector<short> > rowData);
	~Picross();

	void draw();
	void pass();

	inline int getWidth() { return width; }
	inline int getHeight() { return height; }
};