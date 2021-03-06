/*
	Title:						CSGO Lyrics Script Generator

	Description:					Generates a cfg script based lyrics file that allows the player to
									display the lyrics of any song line by line, using only one key bind.

	Original Author:	ThioJoe: www.youtube.com/user/ThioJoe
														 www.youtube.com/user/CacheGaming

	Compiling:				use `make'.
*/

#include <stdio.h>
#include <string>
#include <cstring>
#include <fstream>
#include <csignal>
#include <set>

using namespace std;

bool scanning = true;

void handleSignal(int signal) {
	if (!scanning) {
		exit(signal);
	}
	scanning = false;
}

void printhelp(char progName[]) {
	printf("Usage: %s [-i/--input <file>|-o/--output <file>|-l/--key <key name>|-h/--help]\n"
				 "\tinput = file to read lyrics from, defaults to stdin.\n"
				 "\toutput = file to write the script cfg to, defaults to stdout.\n"
				 "\tkey = key you press to \"sing\" the lyrics.\n"
				 "\thelp = brings up this text.\n", progName);
}

int main(int argc, char* argv[]) {
	printf("\033]0CSGO Lyrics Script Generator\007"); //Sets the title of terminal.
	signal(SIGINT, handleSignal);

	//Initialize Variables
	set<string> lines;
	string key = "MOUSE3"; //Default key to be bound
	string inputName;
	string outputName;
	ofstream outputFile;

	if (argc > 0) {
		int skipping = 0;
		for (int i = 1; i < argc; i++) {
			if (skipping > 0) {
				skipping--;
				continue;
			}
			string arg = string(argv[i]);
			if (arg.compare("-h") == 0 || arg.compare("--help") == 0) {
				printhelp(argv[0]);
				return 0;
			} else if (arg.compare("-i") == 0 || arg.compare("--input") == 0) {
				skipping++;
				if (argc > i) {
					inputName = string(argv[i + 1]);
					continue;
				}
			} else if (arg.compare("-o") == 0 || arg.compare("--output") == 0) {
				skipping++;
				if (argc > i) {
					outputName = string(argv[i + 1]);
					continue;
				}
			} else if (arg.compare("-k") == 0 || arg.compare("--key") == 0) {
				skipping++;
				if (argc > i) {
					key = string(argv[i + 1]);
					continue;
				}
			}
			printf("Arg: %s.\n", arg.c_str());
			printhelp(argv[0]);
			return 1;
		}
	}

	//Creates name for file in filename variable

	//Loads whatever is in lyrics.txt into set line by line
	if (inputName.empty()) {

		while (scanning) {
			char buffer[128];
			scanf("%s", buffer);
			lines.insert(string(buffer));
		}
	} else {
		ifstream lyrics(inputName.c_str());
		if (lyrics.is_open()) {
			string line;
			while (getline(lyrics, line)) {
				if (!line.empty()) {
					lines.insert(line);
				}
			}
		} else {
			printf("Failed to read input file \"%s\": %d.\n", inputName.c_str(), errno);
			exit(errno);
		}
	}

	printf("Found %d lines.\n", lines.size());

	//Creates new text file with given name
	//If it already exists, this erases it's contents
	if (outputName.empty()) {
		printf("No output file specified, printing output.\n");
		string outputString = "bind " + key + " \"next_line\"\n";
		outputString += "alias c0 \"alias next_line c1;\"\n";

		// Write the actual lyrics.
		set<string>::iterator iter = lines.begin();
		for (int i = 0; i < lines.size(); i++) {
			char buffer[256];
			sprintf(buffer, "alias c%d \"say %s; alias next_line c%d;\"\n", i + 1, (*iter).c_str(), i + 2);
			outputString += string(buffer);
			advance(iter, 1);
		}

		// Run it after
		outputString += "c0;";
		printf("Output:\n%s\n", outputString.c_str());
	} else {
		outputFile.open(outputName.c_str());
		if (!outputFile.is_open()) {
			printf("Failed to open %s for reading: %d.\n", outputName.c_str(), errno);
			return errno;
		}
		outputFile << "";
		outputFile.close();

		//Prints initial script info into file
		printf("Saving boostrap section.\n");
		outputFile.open(outputName.c_str(), fstream::out | fstream::app);
		outputFile << "bind " + key + " \"next_line\"\n";
		outputFile << "alias c0 \"alias next_line c1;\"\n";

		//Prints each iteration for however many lines were found
		set<string>::iterator iter = lines.begin();
		for (int i = 0; i < lines.size(); i++) {
			char buffer[256];
			sprintf(buffer, "alias c%d \"say %s; alias next_line c%d;\"\n", i + 1, (*iter).c_str(), i + 2);
			outputFile << buffer;
			advance(iter, 1);
		}

		//Prints c0 at end to be executed
		outputFile << "c0;\n";

		//Close File
		outputFile.close();
	}

	//Write Success
	printf("Finished!\n\nPlace the output in <CSGO>/cfg/ if you didn't set it to output there.\n");

	return 0;
}
