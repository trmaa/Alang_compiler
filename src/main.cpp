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
		std::stringstream input;
		std::fstream input_file(*(argv+1));//, std::ios::in);
		input << input_file.rdbuf();
		input_string = input.str();
	}

	tokenizer_t tokenizer(input_string);
	std::vector<token_t> tokens = tokenizer.tokenize();

	std::string out = tokens_to_assembly(tokens);
	std::printf("%s", out.c_str());
	{
		std::fstream output_file("alang/main.s");
		output_file << out;
	}

	std::printf("LINKING\n");
	std::system("gcc alang/main.s -o program -nostdlib");

	std::exit(0);
}
