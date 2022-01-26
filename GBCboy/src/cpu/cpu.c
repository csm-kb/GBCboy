#include <gbcpu/cpu.h>

void nop(uint8_t* operands) { return; }
void ld_bc_d16(uint8_t* operands) { gbc_regs.BC = *((uint16_t*)operands); }
void ld_bc_a(uint8_t* operands) { gbc_regs.BC = 0xff00 + gbc_regs.A; }
void inc_bc(uint8_t* operands) { gbc_regs.BC += 1; }
void inc_b(uint8_t* operands) { gbc_regs.B += 1; }
void dec_b(uint8_t* operands) { gbc_regs.B -= 1; }
void ld_b_d8(uint8_t* operands) { gbc_regs.B = *operands; }

const struct cpu_instruction_t gbc_optable[256] = {
	/*0x00*/{ "NOP", 0, nop },
	/*0x01*/{ "LD BC, 0x%04X", 2, ld_bc_d16 },
	/*0x02*/{ "LD (BC), A", 0, ld_bc_a },
	/*0x03*/{ "INC BC", 0, inc_bc },
	/*0x04*/{ "INC B", 0, inc_b },
	/*0x05*/{ "DEC B", 0, dec_b },
	/*0x06*/{ "LD B, 0x%02X", 1, ld_b_d8 }
};

char* gbc_cpu_errmsg = NULL;

int gbc_cpu_step()
{
	return 0;
}