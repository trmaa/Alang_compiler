#include "tokenizer.hpp"

tokenizer_t::tokenizer_t(const std::string& src)
: m_src(src) {}

std::vector<token_t> tokenizer_t::tokenize() {
	std::printf("TOKENIZING\n");

	std::vector<token_t> tokens;
	std::string buffer;

	while (this->m_peek().has_value()) {
		if (std::isalpha(this->m_peek().value())) {
			buffer.push_back(this->m_consume());

			while (this->m_peek().has_value() && std::isalnum(this->m_peek().value())) {
				buffer.push_back(this->m_consume());
			}

			if (buffer == "exit") {
				std::printf("\033[1;32m[tokenizer]<debug>\033[1;33mtoken: %s\033[31;0m\n", buffer.c_str());

				tokens.push_back({.type=token_e::_exit});
				buffer.clear();
				continue;
			}	

			std::printf("\033[1;31m[tokenizer] Error: ");
			std::printf("\033[1;33mtoken: %s\033[1;31m is not a token.\n", buffer.c_str());
			std::printf("- Char: %d.\n", this->m_index);
			std::printf("\033[31;0m");
			std::exit(-1);
		}
		if (std::isdigit(this->m_peek().value())) {
			buffer.push_back(this->m_consume());

			while (this->m_peek().has_value() && std::isdigit(this->m_peek().value())) {
				buffer.push_back(this->m_consume());
			}

			std::printf("\033[1;32m[tokenizer]<debug>\033[1;33mtoken: %s\033[31;0m\n", buffer.c_str());

			tokens.push_back({.type=token_e::_int, .value=buffer});
			buffer.clear();
			continue;
		}

		if (this->m_peek().value() == '(') {
			this->m_consume();

			std::printf("\033[1;32m[tokenizer]<debug>\033[1;33mtoken: (\033[31;0m\n");

			tokens.push_back({.type=token_e::_o_par});	
			continue;
		}
		if (this->m_peek().value() == ')') {
			this->m_consume();

			std::printf("\033[1;32m[tokenizer]<debug>\033[1;33mtoken: )\033[31;0m\n");

			tokens.push_back({.type=token_e::_c_par});	
			continue;
		}

		if (this->m_peek().value() == ';') {
			this->m_consume();

			std::printf("\033[1;32m[tokenizer]<debug>\033[1;33mtoken: ;\033[31;0m\n");

			tokens.push_back({.type=token_e::_endl});	
			continue;
		}

		if (this->m_peek().value() == ' ' || this->m_peek().value() == '\n' || this->m_peek().value() == '\0') {
			this->m_consume();

			std::printf("\033[1;32m[tokenizer]<debug>\033[1;33mtoken: empty\033[31;0m\n");

			continue;
		}

		std::printf("\033[1;31m[tokenizer] Error: ");
		std::printf("\033[1;33mtoken: %s\033[1;31m is not a token.\n", buffer.c_str());
		std::printf("- Char: %d.\n", (unsigned int)this->m_index);
		std::printf("\033[31;0m");
		std::exit(-1);
	}
	this->m_index = 0;

	return tokens;
}
