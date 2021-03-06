#include <gbcpu/cpu.h>

void nop(gbc_mem_t* mem, uint8_t* operands) { return; }
void ld_bc_d16(gbc_mem_t* mem, uint8_t* operands) { gbc_regs.BC = *((uint16_t*)operands); }
// TODO: rewrite this to index into memory at BC
void ld_bc_a(gbc_mem_t* mem, uint8_t* operands) { gbc_regs.BC = 0xff00 + gbc_regs.A; }
void inc_bc(gbc_mem_t* mem, uint8_t* operands) { gbc_regs.BC += 1; }
void inc_b(gbc_mem_t* mem, uint8_t* operands) { gbc_regs.B += 1; }
void dec_b(gbc_mem_t* mem, uint8_t* operands) { gbc_regs.B -= 1; }
void ld_b_d8(gbc_mem_t* mem, uint8_t* operands) { gbc_regs.B = *operands; }
void rlca(gbc_mem_t* mem, uint8_t* operands)
{
	// rotate left carry A - fancy bit ops shift CF to lowest bit of A
	gbc_regs.F = 0x10 & (gbc_regs.A = (0xFE & (gbc_regs.A << 1)) | (0x01 & (gbc_regs.F >> 4)));
	gbc_regs.F = 0xE0 & 0x00; // reset flags
}
void ld_a16_sp(gbc_mem_t* mem, uint8_t* operands) { return; };

const struct cpu_instruction_t gbc_optable[256] = {
	/*0x00*/{ "NOP", 0, 4, nop },
	/*0x01*/{ "LD BC, 0x%04X", 2, 12, ld_bc_d16 },
	/*0x02*/{ "LD (BC), A", 0, 8, ld_bc_a },
	/*0x03*/{ "INC BC", 0, 8, inc_bc },
	/*0x04*/{ "INC B", 0, 4, inc_b },
	/*0x05*/{ "DEC B", 0, 4, dec_b },
	/*0x06*/{ "LD B, 0x%02X", 1, 8, ld_b_d8 },
	/*0x07*/{ "RLCA", 0, 4, rlca },
	/*0x08*/{ "LD (a16), SP", 2, 20, ld_a16_sp }
};

char* gbc_cpu_errmsg = NULL;

int gbc_cpu_step(gbc_mem_t* memory)
{
	return 0;
}