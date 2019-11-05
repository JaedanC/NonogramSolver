#include "FileReader.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>
#include <istream>
#include <fstream>
#include <vector>

using namespace std;

FileReader::FileReader(const string& filepath) {
	inputFile.open(filepath.c_str());

	dims = readLine();

	readLine();

	// Width
	for (int i = 0; i < dims[0]; i++) {
		columnData.push_back(readLine());
	}

	readLine();

	// Height
	for (int i = 0; i < dims[1]; i++) {
		rowData.push_back(readLine());
	}

	inputFile.close();
}

vector<short> FileReader::readLine() {
	vector<short> vec;
	{
		string line;
		std::getline(inputFile, line);
		std::istringstream is(line);
		std::copy(std::istream_iterator<short>(is), std::istream_iterator<short>(), std::back_inserter(vec));
	}

	return vec;
}

void FileReader::drawVec(const vector<short>& vec) {
	for (unsigned int i = 0; i < vec.size(); i++) {
		cout << vec[i] << ", ";
	}
	cout << endl;
}

void FileReader::draw() {
	drawVec(dims);
	cout << endl;
	for (unsigned int i = 0; i < columnData.size(); i++) {
		drawVec(columnData[i]);
	}
	cout << endl;
	for (unsigned int i = 0; i < rowData.size(); i++) {
		drawVec(rowData[i]);
	}
	cout << endl;
}

Picross * FileReader::createPicross() {
	return new Picross(dims, columnData, rowData);
}