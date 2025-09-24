#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string>
#include "token.hpp"

int main(int argc, char** argv) {
	if (argc != 2) {
		std::printf("\033[1;31m Syntax error. Expected: ./compiler <file.alang>\n");
		std::printf("\033[31;0m");
	}

	std::string input_string;
	{
		std::stringstream input_file;
		std::fstream input(*(argv+1));//, std::ios::in);
		input_file << input.rdbuf();
		input_string = input_file.str();
	}

	std::vector<token_t> tokens = tokenize(input_string);

	std::exit(0);
}
