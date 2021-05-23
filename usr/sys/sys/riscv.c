// Code common to all RISC-V systems: 32 or 64-bit, 8k vs 8GB, etc.
#include <stdint.h>
#include <inttypes.h>
#include "n200/riscv_encoding.h" // TODO: use more generic version

int misa_extension_imp(char ext)
{
	unsigned long misa = csr_read(CSR_MISA);

	if (misa) {
		if ('A' <= ext && ext <= 'Z')
			return misa & (1 << (ext - 'A'));
		if ('a' <= ext && ext <= 'z')
			return misa & (1 << (ext - 'a'));
		return 0;
	}

	return sbi_platform_misa_extension(sbi_platform_thishart_ptr(), ext);
}

void misa_string(char *out, unsigned int out_sz)
{
	unsigned int i, pos = 0;
	const char valid_isa_order[] = "iemafdqclbjtpvnsuhkorwxyzg";

	if (!out)
		return;

	// The compiler knows the word size of the target.
	int xlen = __riscv_xlen;

	if (5 <= (out_sz - pos)) {
		out[pos++] = 'r';
		out[pos++] = 'v';
		switch (xlen) {
		case 1:
			out[pos++] = '3';
			out[pos++] = '2';
			break;
		case 2:
			out[pos++] = '6';
			out[pos++] = '4';
			break;
		case 3:
			out[pos++] = '1';
			out[pos++] = '2';
			out[pos++] = '8';
			break;
		default:
			return;
		}
	}

	for (i = 0; i < array_size(valid_isa_order) && (pos < out_sz); i++) {
		if (misa_extension_imp(valid_isa_order[i]))
			out[pos++] = valid_isa_order[i];
	}

	if (pos < out_sz)
		out[pos++] = '\0';
}
