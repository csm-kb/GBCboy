#ifndef GBCBOY_MBC_H
#define GBCBOY_MBC_H

#include <gbcpu/types.h>

/// <summary>
/// Linked-list representation of MBC map entries.
/// </summary>
struct gbc_mbc_entry
{
	struct gbc_mbc_entry* prev;
	struct gbc_mbc_entry* next;
	/// <summary> The physical address base for this entry. The MBC controls what happens when this is written/read. </summary>
	uint16_t pbase;
	/// <summary> The virtual address base for this entry. CPU writes and reads use this value. </summary>
	uint16_t vbase;
	/// <summary> The length of the address range for this entry. </summary>
	uint16_t len;
};

#endif//GBCBOY_MBC_H