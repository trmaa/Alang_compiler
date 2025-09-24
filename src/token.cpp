#include "token.hpp"

std::vector<token_t> tokenize(const std::string& str) {
	std::vector<token_t> tokens;
	std::string buffer;

	for (int i = 0; i < str.size()-1; i++) {
		if (std::isalpha(str.at(i))) {
			buffer.push_back(str.at(i));

			while (std::isalnum(str.at(++i))) {
				buffer.push_back(str.at(i));
			}
			i--;

			if (buffer == "return") {
				std::printf("\033[1;32m%s\n", buffer.c_str());

				tokens.push_back({.type=token_e::_return});
				buffer.clear();

				continue;
			}	
		} else if (std::isdigit(str.at(i))) {
			buffer.push_back(str.at(i));

			while (std::isdigit(str.at(++i))) {
				buffer.push_back(str.at(i));
			}
			i--;

			std::printf("\033[1;32m%s\n", buffer.c_str());

			tokens.push_back({.type=token_e::_int, .value=buffer});
			buffer.clear();

			continue;
		}

		if (str.at(i) == ';') {
			std::printf("\033[1;32m;\n");

			tokens.push_back({.type=token_e::_endl});	
			continue;
		}

		if (str.at(i) == ' ' || str.at(i) == '\n') {
			continue;
		}

		std::printf("\033[1;31m[compiler] Error: ");
		std::printf("\033[1;33m%s\033[1;31m is not a token.\n", buffer.c_str());
		std::printf("- Char: %d.\n", i);
		std::printf("\033[31;0m");
		break;
	}	

	return tokens;
}
