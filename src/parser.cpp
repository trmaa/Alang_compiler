#include <cstdio>
#include "parser.hpp"
#include "tokenizer.hpp"

parser_t::parser_t(const std::vector<token_t>& tokens)
: m_tokens(tokens) {

}

std::optional<node::expr_t> parser_t::parse_expr() {
	this->m_consume();
	if (this->m_peak().has_value() && this->m_peak().value().type == token_e::_int) {
		return node::expr_t{._int=this->m_consume()};
	}
	return {};
}

std::optional<node::exit_t> parser_t::parse() {
	std::printf("PARSING\n");

	node::exit_t exit_node;
	while (this->m_peak().has_value()) {
		if (this->m_peak().value().type == token_e::_exit) {
			if (auto expr_node = this->parse_expr()) {
				exit_node = {.expr=expr_node.value()};
				continue;
			} else {
				std::printf("\033[1;31m[parser] Error: exit must have an argument.\n");
				std::printf("\033[31;0m");
				std::exit(-1);
			}
		}
		if (this->m_peak().has_value() && this->m_peak().value().type == token_e::_endl) {
			this->m_consume();
			continue;
		} else {
			std::printf("\033[1;31m[parser] Error: missed a ;.\n");
			std::printf("\033[31;0m");
			std::exit(-1);
		}
	}
	this->m_index = 0;
	return exit_node;
}
