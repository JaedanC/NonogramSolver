#include <iostream>
#include "FileReader.h"
#include <vector>
#include <string>
#include "Timer.h"

using namespace std;

/*
Takes in a file to a picross and then starts the solver. Press
enter to complete a generation.
*/
void solve(const char* filename) {
	FileReader fr(filename);

	Picross* p = fr.createPicross();

	int passes = 0;
	while (true)
	{
		cout << "Press enter to compute generation " << ++passes << ".\nInput q to exit solver.\n";
		char c = cin.get();
		if (c == 'q') break;

		{
			Timer t;
			p->pass();
			p->draw();
		}
	}

	delete p;
}

bool is_file_exist(const char* fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}

void printUsage() {
	cout << "Usage:\n";
	cout << "./PicrossSolver <filename> <filename2> <filename3...etc>\n";
	cout << "Use --help for Picross file format.\n\n";
	cout << "Press enter to exit\n";
	cin.get();
}

void printHelp() {
	cout << "Example file format.\n";
	cout << "small.txt\n";
	cout << "5 5\t\t # Size of picross n x m\n\n";
	cout << "1\t\t # Column Data\n2 2\n1\n1\n0\n\n";
	cout << "1\t\t # Row Data\n1\n1 2\n1\n1\n";
}

int main(int argc, char ** argv) {
	if (argc == 1) {
		printUsage();
		return 0;
	}

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--help") == 0) {
			printHelp();
			break;
		}
	}

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--help") == 0) continue;

		if (is_file_exist(argv[i])) {
			cout << "Solving '" << argv[i] << "'.\n";
			solve(argv[i]);
		}
		else {
			cout << "File '" << argv[i] << "' Does not exist. Skipping.\n";
		}
	}

	cout << "Press enter to exit\n";
	cin.get();
}
