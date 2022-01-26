#ifndef GBCBOY_CPU_H
#define GBCBOY_CPU_H

#include <stdint.h>

/// <summary>
/// Represents a GBC's CPU registers.
/// </summary>
struct gbc_reg_t
{
	union
	{
		struct {
			uint8_t F;	// flag register
			uint8_t A;
		};
		uint16_t AF;
	};
	union
	{
		struct {
			uint8_t C;
			uint8_t B;
		};
		uint16_t BC;
	};
	union
	{
		struct {
			uint8_t E;
			uint8_t D;
		};
		uint16_t DE;
	};
	union
	{
		struct {
			uint8_t L;
			uint8_t H;
		};
		uint16_t HL;
	};
	uint16_t SP;
	uint16_t PC;
}
extern gbc_regs;

/// <summary>
/// A CPU instruction type that encapsulates assembly, operand length, and function pointer.
/// </summary>
struct cpu_instruction_t
{
	char* asm;
	uint8_t op_len;
	void* execute;
} extern const gbc_optable[256];

extern char* gbc_cpu_errmsg;

/// <summary>
/// Executes a single step for the CPU, given a pointer into memory.
/// </summary>
/// <returns>0 on success, anything else + writes an error message to <c>gbc_cpu_errmsg</c> on failure.</returns>
extern int gbc_cpu_step();

#endif//GBCBOY_CPU_H