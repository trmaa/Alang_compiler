#include "generator.hpp"
#include <sstream>

generator_t::generator_t(const node::exit_t& root)
: m_root(root) {

}

std::string generator_t::generate() {
	std::printf("COMPILING\n");

	std::stringstream output;

	output << ".section .text\n.globl _start\n_start:\n";

	output << "	movq $60, %rax\n";
	output << "	movq $" << this->m_root.expr._int.value.value() << ", %rdi\n";
	output << "	syscall\n";

	return output.str();
}
