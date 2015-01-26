#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>


//#define PCRE2_CODE_UNIT_WIDTH 16
//#include "src/config.h"
#include <pcre++.h>

#define FILEPATH_PARAMETER "-f"
#define MISSING_PARAM_MSG "Use parameter -f to define a filepath\n"
#define MISSING_FILE_MSG "File not found\n"

#define TC_EXPRESSION "\"[A-Z]{6}\""

void tcFromString(std::string *file, std::vector<std::string> *tc){
	
	// pcrepp::Pcre reg("[A-Z]{6}", "i");
    
  //   if(reg.search(*file) == true) {
		// for(int pos=0; pos < reg.matches(); pos++) {
		//   std::cout << "  substring " << pos << ": " << reg.get_match(pos);
		//   std::cout << " (start: " << reg.get_match_start(pos) << ", end: "
		//        << reg.get_match_end(pos) << ")" << std::endl;
		// }
  //   }
	
}

int main(int argc, char ** argv){
	std::string filepath;

	for(int i = 0; i< argc; i++){
	   	if(strncmp(argv[i], FILEPATH_PARAMETER, 2) == 0){
	   		filepath = argv[i+1];
	   		break;
	   	}
	}

	if(filepath.empty() == true){
		printf(MISSING_PARAM_MSG);
		return -1;
	}
	printf("using file %s\n", filepath.c_str());

	std::ifstream filestream(filepath);

	if(filestream.fail()){
		printf(MISSING_FILE_MSG);
		return -1;
	}

	std::stringstream buffer;
	buffer << filestream.rdbuf();
	std::string filecontent = buffer.str();

	std::vector<std::string> tcCommands;
	tcFromString(&filecontent, &tcCommands);
}