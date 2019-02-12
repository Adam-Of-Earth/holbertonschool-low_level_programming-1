#include <stdio.h>

#define div_96(op1_hi, op1_mid, op1_lo, op2_hi, op2_mid, op2_lo) \
do { \
	int den_96_1, den_96_2, den_96_3, den_96_4, den_96_5, den_96_6; \
	int num_96_1, num_96_2, num_96_3, num_96_4, num_96_5, num_96_6; \
	int rem_96_1, rem_96_2, rem_96_3, rem_96_4, rem_96_5; \
\
	den_96_1 = (op2_hi) >> 16; \
	den_96_2 = (op2_hi) & 0xFFFF; \
	den_96_3 = (op2_mid) >> 16; \
	den_96_4 = (op2_mid) & 0xFFFF; \
	den_96_5 = (op2_lo) >> 16; \
	den_96_6 = (op2_lo) & 0xFFFF; \
	num_96_1 = (op1_hi) >> 16; \
	num_96_2 = (op1_hi) & 0xFFFF; \
	num_96_3 = (op1_mid) >> 16; \
	num_96_4 = (op1_mid) & 0xFFFF; \
	num_96_5 = (op1_lo) >> 16; \
	num_96_6 = (op1_lo) & 0xFFFF; \
\
	(op1_hi) = ((num_96_1 << 16) | num_96_2) / den_96_1 << 16; \
	printf("%x %x %x %x\n", num_96_1, num_96_2, den_96_1, op1_hi); \
	rem_96_1 = ((num_96_1 << 16) | num_96_2) % den_96_1; \
	(op1_hi) &= ( \
		((rem_96_1 << 16) | num_96_3) - \
		((op1_hi) >> 16) * den_96_2 \
	) / den_96_1 & 0xFFFF; \
	rem_96_2 = ( \
		((rem_96_1 << 16) | num_96_3) - \
		((op1_hi) >> 16) * den_96_2 \
	) % den_96_1; \
	op1_mid = ( \
		((rem_96_2 << 16) | num_96_4) - \
		((op1_hi) & 0xFFFF) * den_96_2 - \
		((op1_hi) >> 16) * den_96_3 \
	) / den_96_1 << 16; \
	rem_96_3 = ( \
		((rem_96_2 << 16) | num_96_4) - \
		((op1_hi) & 0xFFFF) * den_96_2 - \
		((op1_hi) >> 16) * den_96_3 \
	) % den_96_1; \
	op1_mid &= ( \
		((rem_96_3 << 16) | num_96_5) - \
		((op1_mid) >> 16) * den_96_2 - \
		((op1_hi) & 0xFFFF) * den_96_3 - \
		((op1_hi) >> 16) * den_96_4 \
	) / den_96_1 & 0xFFFF; \
	rem_96_4 = ( \
		((rem_96_3 << 16) | num_96_5) - \
		((op1_mid) >> 16) * den_96_2 - \
		((op1_hi) & 0xFFFF) * den_96_3 - \
		((op1_hi) >> 16) * den_96_4 \
	) % den_96_1; \
	op1_lo = ( \
		((rem_96_4 << 16) | num_96_6) - \
		((op1_mid) & 0xFFFF) * den_96_2 - \
		((op1_mid) >> 16) * den_96_3 - \
		((op1_hi) & 0xFFFF) * den_96_4 - \
		((op1_hi) >> 16) * den_96_5 \
	) / den_96_1 << 16; \
	rem_96_5 = ( \
		((rem_96_4 << 16) | num_96_6) - \
		((op1_mid) & 0xFFFF) * den_96_2 - \
		((op1_mid) >> 16) * den_96_3 - \
		((op1_hi) & 0xFFFF) * den_96_4 - \
		((op1_hi) >> 16) * den_96_5 \
	) % den_96_1; \
	op1_lo &= ( \
		(rem_96_5 << 16) - \
		((op1_lo) >> 16) * den_96_2 - \
		((op1_mid) & 0xFFFF) * den_96_3 - \
		((op1_mid) >> 16) * den_96_4 - \
		((op1_hi) & 0xFFFF) * den_96_5 - \
		((op1_hi) >> 16) * den_96_6 \
	) / den_96_1 & 0xFFFF; \
} while (0)

/**
 * main - Entry point
 *
 * Return: 0
 */
int main(void)
{
	int op1_hi = 0x80000, op1_mid = 0x80000, op1_lo = 0x80000;
	int op2_hi = 0x20000, op2_mid = 0x20000, op2_lo = 0x20000;

	div_96(op1_hi, op1_mid, op1_lo, op2_hi, op2_mid, op2_lo);
	printf("%x %x %x\n", op1_hi, op1_mid, op1_lo);
	return (0);
}
