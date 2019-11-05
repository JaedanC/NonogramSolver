#pragma once
#include <vector>
#include <string>

/* This class holds a column or a row as an array of pointers to the actual
value in the grid. This way we abstract out the columns vs rows and we can just solve
using this one data type. */
class Row {
	std::vector<short> gapData;
	short** row;
	short* combRow;
	short* keepRow;
	int length;
	int bars;

	/* This function takes in a bars (number of black spaces in gap data) and
	stars (which are the amount of whitespaces that we can distribute). It then outputs
	every combination of this setup recursively. This function actually write the result
	to a string. This string is then passed onto concatenateCombination() one at a time. */
	bool barsAndStars(int bars, int stars, std::string prefix = "");

	/* This is where the magic happens. Firstly, this function turns the string
	from barsAndStars into a vector of shorts. Then it generates the line that
	is produced using this barAndStar combination. Then using this result, and the
	results of every barsAndStars call afterwards, it culls combinations that are
	impossible given the given state of the board and then concatenates the passing
	lines into a single line that has every element that was the same as ON or OFF.
	Entries that are conflicting, are set to UNKNOWN. Finally once this final line
	has been generated it is merged into the row pointers changing the grid.*/
	bool concatenateCombination(const std::string& comb);
public:
	/* Takes in the length of the row and a heap allocated array of pointers which
	are our real values in the the grid. The gapData is from the parsedFile and contains
	this rows gap data eg, {1, 5, 6}. */
	Row(int length, short** row, std::vector<short> gapData);

	/* Supposed to free the allocated memory however does not work. Currently still under
	investigation why this doesn't work. Right now there are memory leaks since the new
	memory is not freed.*/
	void free();

	/* Draws a concise representation of the row's current state and our gapData. */
	void draw();

	/* Using bars and stars brute force, we compute one pass on the row to determine more guaranteed
	squares.*/
	void pass();

};