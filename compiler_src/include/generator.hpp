#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "parser.hpp"

class generator_t {
private:
	const node::exit_t& m_root;

public:
	std::string generate();

public:
	generator_t(const node::exit_t& root);
};

#endif
