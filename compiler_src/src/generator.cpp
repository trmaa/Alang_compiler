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

	std::printf("\033[1;32m[compiler]<debug>\n\033[1;33m%s\033[31;0m", output.str().c_str());

	return output.str();
}
