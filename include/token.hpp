#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <cctype>
#include <optional>
#include <string>
#include <vector>

enum token_e {
	_return,
	_int,
	_endl
};

typedef struct token_t {
	token_e type;
	std::optional<std::string> value{};
} token_t;

std::vector<token_t> tokenize(const std::string& str);

#endif
