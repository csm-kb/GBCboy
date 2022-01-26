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
			/// <summary>
			///	<c>0bZNHC0000</c><para/>
			/// 7 = Z: Zero flag (0x80)<para/>
			///	6 = N: Subtract flag (0x40)<para/>
			///	5 = H: Half Carry flag (0x20)<para/>
			///	4 = C: Carry flag (0x10)<para/>
			///	Rest are unused. (F: 0-7)
			/// </summary>
			uint8_t F;
			uint8_t A;	// register A (8-15)
		};
		uint16_t AF;
	};
	union
	{
		struct {
			uint8_t C;	// register C (0-7)
			uint8_t B;	// register B (8-15)
		};
		uint16_t BC;
	};
	union
	{
		struct {
			uint8_t E;	// register E (0-7)
			uint8_t D;	// register D (8-15)
		};
		uint16_t DE;
	};
	union
	{
		struct {
			uint8_t L;	// register L (0-7)
			uint8_t H;	// register H (8-15)
		};
		uint16_t HL;
	};
	uint16_t SP;	// stack pointer
	uint16_t PC;	// program counter
}
extern gbc_regs;

/// <summary>
/// A CPU instruction type that encapsulates assembly, operand length, and function pointer.
/// </summary>
struct cpu_instruction_t
{
	char* asm;		// visible format string for the instruction
	uint8_t op_len;	// length of operands in bytes
	uint8_t cycles;	// number of cycles to execute
	void* execute;	// function pointer to execution for instruction
} extern const gbc_optable[256];

extern char* gbc_cpu_errmsg;

/// <summary>
/// Executes a single step for the CPU, given a pointer into memory.
/// </summary>
/// <returns>0 on success, anything else + writes an error message to <c>gbc_cpu_errmsg</c> on failure.</returns>
extern int gbc_cpu_step();

#endif//GBCBOY_CPU_H