#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "Picross.h"

class FileReader {
	std::ifstream inputFile;
	std::vector<short> readLine();
	void drawVec(const std::vector<short>& vec);

public:
	std::vector< std::vector<short> > columnData;
	std::vector< std::vector<short> > rowData;
	std::vector<short> dims;

	Picross * createPicross();

	FileReader(const std::string& filepath);

	void draw();
};