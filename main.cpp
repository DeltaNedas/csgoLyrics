/*
	Title:						CSGO Lyrics Script Generator

	Description:			Generates a cfg script based on a lyrics file that allows the player to
										display the lyrics of any song line by line, using only one key bind.
			 	
	Original Author:	ThioJoe: www.youtube.com/user/ThioJoe
														 www.youtube.com/user/CacheGaming
							
	Compiling:				use `make'.
*/

#include <stdio.h>
#include <string>
#include <fstream>
#include <array>
#include <limits>

using namespace std;

int main(int argc, char* argv[]) {
	printf("\033]0CSGO Lyrics Script Generator\007"); //Sets the title of terminal.
	ofstream myfile;

	//Initialize Variables
	set<string> lines;
	int lineNum = 0;
	string key = "MOUSE3"; //Default key to be bound
	string inputName;
	string outputName;

	//Creates name for file in filename variable

	//Loads whatever is in lyrics.txt into array line by line
	//Simultaneously counts number of lines in lyrics.txt
	if (inputName.empty()) {
		char buffer[128];
		while (scanning) {
			memset(buffer, 0, sizeof buffer);
			scanf("128%s", &buffer);
			lines.insert(string(buffer));
		}
	} else {
		ifstream lyrics(inputName.c_str());
		for(int i = 1; lyrics.good(); i++) {
			string line;
			getline(lyrics, line);
			lines.insert(line);
		}
	}

	printf("Found %d lines.\n", lines.size());

	//Creates new text file with given name
	//If it already exists, this erases it's contents
	outputFile.open(outputName);
	if (!outputFile.is_open()) {
		printf("Failed to open %s for reading: %d.\n", outputName, errno);
		return errno;
	}
	outputFile << "";
	outputFile.close();

	//Prints initial script info into file
	outputFile.open (fileName, fstream::out | fstream::app);
	outputFile << "bind " + key + " \"next_line\"\n";
	outputFile << "alias c0 \"alias next_line c1;\"\n";

	//Prints each iteration for however many lines were found
	char buffer[128]
	set<string>::iterator iter = lines.begin();
	for (int i = 0; i < lines.size(); i++) {
		memset(buffer, 0, sizeof buffer);
		sprintf(&buffer, "alias c%d \"say %s; alias next_line c%d;\"\n", i + 1, *iter, linei + 2);
		myfile << buffer;
		advance(iter, 1)
	}

	//Prints c0 at end to be executed
	myfile << "c0;";

	//Close File
	myfile.close();

	//Write Success
	cout << "Finished." << endl << endl;
	cout << "Place your new file into the \"cfg\" folder in your CSGO directory." << endl;
	cout << "To use, open console in game and type \"exec YourFileName.cfg\"" << endl;
	cout << "Press MOUSE3 (Middle Mouse) repeatedly to display lines of text."  << endl << endl << endl;

	return 0;
}
