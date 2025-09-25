#ifndef TOKENIZER_HPP 
#define TOKENIZER_HPP

#include <optional>
#include <string>
#include <vector>

enum token_e {
	_exit,
	_int,
	_endl,
	_o_par,
	_c_par
};

typedef struct token_t {
	token_e type;
	std::optional<std::string> value{};
} token_t;

std::string tokens_to_assembly(const std::vector<token_t>& tokens);

class tokenizer_t {
private:
	const std::string& m_src;
	size_t m_index = 0;

private:
	std::optional<char> m_peek(int ahead = 0) const {
		if (this->m_index + ahead >= this->m_src.size()) {
			return {};
		}	
		return this->m_src.at(this->m_index + ahead);
	}

	char m_consume() {
		return this->m_src.at(this->m_index++);
	}
public:
	std::vector<token_t> tokenize();

public:
	tokenizer_t(const std::string& src);
};

#endif
