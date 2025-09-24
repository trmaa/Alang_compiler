#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string>
#include "generator.hpp"
#include "parser.hpp"
#include "tokenizer.hpp"

int main(int argc, char** argv) {
	if (argc != 2) {
		std::printf("\033[1;31m Syntax error. Expected: ./compiler <file.alang>\n");
		std::printf("\033[31;0m");
		std::exit(-1);
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

	parser_t parser(tokens);
	std::optional<node::exit_t> tree = parser.parse();

	if (!tree.has_value()) {
		std::printf("\033[1;31m [parser] Syntax error.\n");
		std::printf("\033[31;0m");
		std::exit(-1);
	}

	generator_t generator(tree.value());
	{
		std::fstream output_file("alang/main.s");
		output_file << "";
		output_file << generator.generate();
	}

	std::printf("ASSEMBLING\n");
	std::printf("LINKING\n");
	std::system("gcc alang/main.s -o alang.app -nostdlib");

	std::exit(0);
}
