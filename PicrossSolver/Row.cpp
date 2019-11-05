#include "Row.h"
#include <iostream>
#include <sstream>
#include <iterator>
#include <mutex>

using namespace std;

//std::mutex grid_mutex;
//int joined_threads = 0;

Row::Row(int length, short** row, std::vector<short> gapData)
	: length(length), row(row), gapData(gapData)
{
	bars = gapData.size();
	combRow = new short[length];
	keepRow = new short[length];
}

void Row::draw() {
	cout << "|";
	for (int i = 0; i < length; i++) {
		cout << *row[i];
	}
	cout << "| ";
	for (unsigned int i = 0; i < gapData.size(); i++) {
		cout << gapData[i] << ", ";
	}
	cout << endl;
}

void Row::free() {
	//delete[] combRow;
	//delete[] keepRow;
}

void Row::pass() {
	// Reset keepRow every pass.
	memset(keepRow, -1, length * sizeof(short));


	int stars = length - bars + 1;
	for (unsigned int i = 0; i < gapData.size(); i++) {
		stars -= gapData[i];
	}

	barsAndStars(bars, stars);


	//grid_mutex.lock();
	//draw();
	// Merge keepRow with row
	for (int i = 0; i < length; i++) {
		if (keepRow[i] > 0) {
			*row[i] = keepRow[i];
		}
	}
	//grid_mutex.unlock();
}

bool Row::barsAndStars(int bars, int stars, string prefix) {
	string comb;
	if (stars == 0) {
		comb += prefix;
		for (int i = 0; i < bars + 1; i++) {
			comb += "0 ";
		}
		return concatenateCombination(comb);
	}

	if (bars == 0) {
		comb += prefix + to_string(stars);

		return concatenateCombination(comb);
	}

	for (int i = 0; i < stars + 1; i++) {
		if (!barsAndStars(bars - 1, stars - i, prefix + std::to_string(i) + " ")) {
			return false;
		}
	}

	return true;
}

bool Row::concatenateCombination(const string& comb)
{
	/* Convert the string into something useful*/
	vector<short> vec;
	std::istringstream is(comb);
	std::copy(std::istream_iterator<short>(is), std::istream_iterator<short>(), std::back_inserter(vec));

	/* Set the combination row to be something garbage. */
	memset(combRow, -5, length * sizeof(short));

	/* Generate the potential line from bars and stars. This is done by
	alternating between gapData and the short vector we made above. The vec above
	should always be one item longer than gapData thus we need to do one more pass
	at the end to not miss the final element of vec. */
	int currentIndex = 0;
	for (unsigned int i = 0; i < gapData.size(); i++) {
		int whiteHere = vec[i];
		int thenBlackHere = gapData[i];

		for (int m = 0; m < whiteHere; m++) {
			combRow[currentIndex] = 1;
			currentIndex++;
		}

		for (int m = 0; m < thenBlackHere; m++) {
			combRow[currentIndex] = 2;
			currentIndex++;
		}

		if (currentIndex != length - 1) {
			combRow[currentIndex] = 1;
		}
		currentIndex++;
	}

	currentIndex--;
	int whiteHere = vec[gapData.size()];
	for (int m = 0; m < whiteHere; m++) {
		combRow[currentIndex] = 1;
		currentIndex++;
	}

	// Combination row is two (black) or one (white) pretty simple.
	// Keep row initially is -1, becomes 1 or 0 based on the next input
	// If another kept combRow is found that is different to 1 or 0 then
	// set this square to be 0. Aka still unknown.
	// Rows that are kept are ones that when row[i] != unknown (0) 
	// row[i] == combRow[i]

	/* If this row conflicts with what we already have then discard the row. */
	for (int i = 0; i < length; i++) {
		if (*row[i] != 0 && *row[i] != combRow[i]) {
			// This square already has an answer in it
			return true;
		}
	}

	/* Concatenate this row on the go with another keepRow which will be merged
	into the real row. This method significantly reduces memory usage from my java
	version by not storing every comination but using it and concatenating as we go.
	Might be slower, but uses WAY less memory.
	0 == Unknown
	1 == BLACK
	2 == WHITE
	-1 == keepRow empty. Override it immediately and assume it's true. */
	for (int i = 0; i < length; i++) {
		if (keepRow[i] == -1) {
			keepRow[i] = combRow[i];
			continue;
		}

		if (keepRow[i] == 0) {
			continue;
		}

		if (keepRow[i] != combRow[i]) {
			keepRow[i] = 0;
			continue;
		}
	}

	int counter = 0;
	for (int i = 0; i < length; i++) {
		if (keepRow[i] == 0) {
			counter++;
		}
	}
	if (counter == length) {
		return false;
	}
	return true;
}