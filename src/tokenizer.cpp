#include <sstream>
#include "tokenizer.hpp"

tokenizer_t::tokenizer_t(const std::string& src)
: m_src(src) {}

std::vector<token_t> tokenizer_t::tokenize() {
	std::printf("TOKENIZING\n");

	std::vector<token_t> tokens;
	std::string buffer;

	while (this->m_peak() != '\0') {
		if (std::isalpha(this->m_peak())) {
			buffer.push_back(this->m_consume());

			while (this->m_peak() != '\0' && std::isalnum(this->m_peak())) {
				buffer.push_back(this->m_consume());
			}

			if (buffer == "exit") {
				tokens.push_back({.type=token_e::_exit});
				buffer.clear();

				continue;
			}	
		} else if (std::isdigit(this->m_peak())) {
			buffer.push_back(this->m_consume());

			while (std::isdigit(this->m_peak())) {
				buffer.push_back(this->m_consume());
			}

			tokens.push_back({.type=token_e::_int, .value=buffer});
			buffer.clear();

			continue;
		}

		if (this->m_peak() == ';') {
			this->m_consume();

			tokens.push_back({.type=token_e::_endl});	
			continue;
		}

		if (this->m_peak() == ' ' || this->m_peak() == '\n') {
			this->m_consume();

			continue;
		}

		std::printf("\033[1;31m[tokenizer] Error: ");
		std::printf("\033[1;33m%s\033[1;31m is not a token.\n", buffer.c_str());
		std::printf("- Char: %d.\n", this->m_index);
		std::printf("\033[31;0m");
		std::exit(-1);
	}
	this->m_index = 0;

	return tokens;
}

std::string tokens_to_assembly(const std::vector<token_t>& tokens) {
	std::printf("COMPILING\n");

	std::stringstream output;

	output << ".section .text\n.globl _start\n_start:\n";

	for (int i = 0; i < tokens.size(); i++) {
		token_t token = tokens.at(i);
		if (token.type == token_e::_exit) {
			if (
				!(i + 1 < tokens.size()) 
				|| !(tokens.at(i+1).type == token_e::_int)

				|| !(i + 2 < tokens.size())
				|| !(tokens.at(i+2).type == token_e::_endl)
			) {
				std::printf("\033[1;31m[compiler] Error: ");
				std::printf("\033[1;33mreturn\033[1;31m needs a value.\n");
				std::printf("\033[31;0m");
				std::exit(-1);
			}

			output << "	movq $60, %rax\n";
			output << "	movq $" << tokens.at(i+1).value.value() << ", %rdi\n";
			output << "	syscall\n";
		}
	}

	return output.str();
}
