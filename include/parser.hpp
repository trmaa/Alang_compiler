#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include "tokenizer.hpp"

namespace node {
	typedef struct expr_t {
		token_t _int;
	} expr_t;

	typedef struct exit_t {
		node::expr_t expr;
	} exit_t;
};

class parser_t {
private:
	const std::vector<token_t>& m_tokens;
	size_t m_index = 0;

private:
	std::optional<token_t> m_peak(int ahead = 1) const {
		if (this->m_index + ahead >= this->m_tokens.size()) {
			return {};
		}	
		return this->m_tokens.at(this->m_index);
	}

	token_t m_consume() {
		return this->m_tokens.at(this->m_index++);
	}
public:
	std::optional<node::expr_t> parse_expr();

	std::optional<node::exit_t> parse();

public:
	parser_t(const std::vector<token_t>& tokens);
};

#endif
