#include "stdafx.h"
#include <stdio.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <regex>

#define FILEPATH_PARAMETER "-f"
#define MISSING_PARAM_MSG "Use parameter -f to define a filepath\n"
#define MISSING_FILE_MSG "File not found\n"

#define TC_PATTERN std::regex("\"([A-Z]{6})\"")
#define COMMENT_PATTERN std::regex("\\/\\*(.*?)\\*\\/|\\/\\/(.*?)$")

#define OUTPUT_FILENAME "tc_commands.txt"

void tcFromString(std::vector<std::string> file, std::vector<std::string> tc){
	int cnt = 0;
	std::ofstream myfile;

	myfile.open(OUTPUT_FILENAME);
	myfile << "TC PARAMS - SkyNetProject\n";
	myfile << "----------" << std::endl;

	for (size_t line = 0; line < file.size(); line++){
		std::smatch matches;
		std::regex_search(file[line], matches, TC_PATTERN);
		
		if (matches.size() > 1){
			myfile << matches[1] << " ";
			
			//search for comment/explanation of TC command
			std::smatch comments;
			
			std::regex_search(file[line], comments, COMMENT_PATTERN);
			if (comments.size() > 0){
				myfile << " - " << comments[0];
			}
			
			myfile << std::endl;
			cnt++;
		}
	}
	myfile << "----------" << std::endl;
	myfile << cnt << " TC commands supported" << std::endl;
	myfile.close();
}

bool filepathHasExtraCharacters(std::string filepath){
	const char* str = filepath.c_str();

	return ((strncmp(str, "\'", 1) == 0)
		|| (strncmp(str, "\"", 1) == 0));
}

std::string cutExtraCharacters(std::string filepath){
	return filepath.substr(1, filepath.size() - 2);
}

int main(int argc, char ** argv){
	std::string filepath;

	for (int i = 0; i< argc; i++){
		//printf("%d: %s\n", i+1, argv[i]);

		if (strncmp(argv[i], FILEPATH_PARAMETER, 2) == 0){
			filepath = argv[i + 1];
			break;
		}
	}

	if (filepath.empty() == true){
		printf(MISSING_PARAM_MSG);
		return -1;
	}

	if (filepathHasExtraCharacters(filepath)){
		filepath = cutExtraCharacters(filepath);
	}

	printf("using file %s\n", filepath.c_str());

	std::ifstream filestream(filepath.c_str());

	if (filestream.fail()){
		printf(MISSING_FILE_MSG);
		return -1;
	}
	std::vector <std::string> filecontent;
	std::string line;
	while (std::getline(filestream, line)){
		filecontent.push_back(line);
	}
	// std::stringstream buffer;
	// buffer << filestream.rdbuf();
	// std::string filecontent = buffer.str();

	std::vector<std::string> tcCommands;
	tcFromString(filecontent, tcCommands);

	return 0;
}
