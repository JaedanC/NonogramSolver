#include "Picross.h"
#include <iostream>
#include <assert.h>
#include <thread>
#include "Row.h"

using namespace std;

Picross::Picross(
	std::vector<short> dims, 
	std::vector<std::vector<short> > columnData,
	std::vector<std::vector<short> > rowData)
{
	width = dims[0];
	height = dims[1];

	grid = new short*[height];

	for (int i = 0; i < height; i++) {
		grid[i] = new short[width];
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			grid[i][j] = 0;
		}
	}

	for (int i = 0; i < height; i++) {
		short** row = new short*[width];
		for (int j = 0; j < width; j++) {
			row[j] = &grid[i][j];
		}
		allRows.emplace_back(width, row, rowData[i]);
	}

	for (int i = 0; i < width; i++) {
		short** row = new short*[height];
		for (int j = 0; j < height; j++) {
			row[j] = &grid[j][i];
		}
		allRows.emplace_back(height, row, columnData[i]);
	}

	/*for (int i = 0; i < allRows.size(); i++) {
		allRows[i].draw();
	}*/
}

Picross::~Picross() {
	for (int i = 0; i < height; i++) {
		delete[] grid[i];
	}
	delete[] grid;
}

void Picross::draw() {
	for (int i = 0; i < height; i++) {
		cout << "|";
		for (int j = 0; j < width; j++) {
			switch (grid[i][j]) {
			case 0:
				// Unknown
				cout << "-";
				break;
			case 1:
				cout << " ";
				break;
			case 2:
				cout << "O";
				break;
			default:
				assert(false);
			}
			cout << " ";
		}
		cout << "|" << endl;
	}
	cout << endl;
}

void Picross::pass() {


	//vector<thread> threads;
	for (unsigned int i = 0; i < allRows.size(); i++) {
		//threads.emplace_back(&Row::pass, allRows[i]);
		allRows[i].pass();
	}

	/*for (int i = 0; i < allRows.size(); i++) {
		threads[i].join();
	}*/
}