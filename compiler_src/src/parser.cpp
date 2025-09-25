#include <cstdio>
#include "parser.hpp"
#include "tokenizer.hpp"

parser_t::parser_t(const std::vector<token_t>& tokens)
: m_tokens(tokens) {

}

std::optional<node::expr_t> parser_t::parse_expr() {
	std::optional<node::expr_t> node = {};
	if (this->m_peek().has_value() && this->m_peek().value().type == token_e::_o_par) {
		this->m_consume();
	} else {
		std::printf("\033[1;31m[parser] error: missing (.\n");
		std::printf("\033[31;0m");
		std::exit(-1);
	}
	if (this->m_peek().has_value() && this->m_peek().value().type == token_e::_int) {
		node = node::expr_t{._int=this->m_consume()};
	} else {
		std::printf("\033[1;31m[parser] error: missing argument.\n");
		std::printf("\033[31;0m");
		std::exit(-1);
	}
	if (this->m_peek().has_value() && this->m_peek().value().type == token_e::_c_par) {
		this->m_consume();
	} else {
		std::printf("\033[1;31m[parser] error: missing ).\n");
		std::printf("\033[31;0m");
		std::exit(-1);
	}
	return node;
}

std::optional<node::exit_t> parser_t::parse() {
	std::printf("PARSING\n");

	node::exit_t exit_node;
	while (this->m_peek().has_value()) {
		if (this->m_peek().value().type == token_e::_exit) {
			this->m_consume();

			std::printf("\033[1;32m[parser]<debug>\033[1;33mnode: exit\033[31;0m\n");

			if (auto expr_node = this->parse_expr()) {
				std::printf("\033[1;32m[parser]<debug>\033[1;33m	arg: %s\033[31;0m\n", 
					expr_node.value()._int.value->c_str());

				exit_node = {.expr=expr_node.value()};
				continue;
			}	

			std::printf("\033[1;31m[parser] error: missing (argument).\n");
			std::printf("\033[31;0m");
			std::exit(-1);
		}
		if (this->m_peek().has_value() && this->m_peek().value().type == token_e::_endl) {
			this->m_consume();

			std::printf("\033[1;32m[parser]<debug>\033[1;33mnode: ;\033[31;0m\n");

			continue;
		}
	}
	this->m_index = 0;
	return exit_node;
}
