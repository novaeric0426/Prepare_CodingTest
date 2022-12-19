#include<iostream>


using namespace std;

const int kNumUnsignBits = 64;

short CountBits(unsigned int x) {
	short num_bits = 0;
	while (x) {
		num_bits += x & 1;
		x >>= 1;
	}
	return num_bits;
}

short Parity(unsigned long x) {
	short result = 0;
	while (x) {
		result ^= 1;
		x &= (x - 1);
	}
	return result;
}

short Parity_Better(unsigned long x) {
	x ^= x >> 32;
	x ^= x >> 16;
	x ^= x >> 8;
	x ^= x >> 4;
	x ^= x >> 2;
	x ^= x >> 1;
	return x ^ 0x1;
}

long SwapBits(long x, int i, int j) {
	if (((x >> i) & 1) != ((x >> j) & 1)){
		unsigned long bit_mask = (1L << i) | (1L << j);
		x ^= bit_mask;
	}
	return x;
}

unsigned long ClosestIntSameBitCount(unsigned long x) {
	for (int i = 0; i < kNumUnsignBits; i++) {
		if (((x >> i) & 1) != ((x >> (i + 1)) & 1)) {
			x ^= (1UL << i) | (1UL << (i + 1));
			return x;
		}
	}
	throw invalid_argument("All bits are 0 or 1");
}

long Reverse(int x) {
	long result = 0; long x_remaining = abs(x);
	while (x_remaining) {
		result = result * 10 + x_remaining % 10;
		x_remaining /= 10;
	}
	return x < 0 ? -result : result;
}

bool IsPalindromeNumber(int x) {
	if (x < 0) {
		return false;
	}
	const int num_digits = static_cast<int>(floor(log10(x))) + 1;
	int msd_mask = static_cast<int>(pow(10, num_digits - 1));
	for (int i = 0; i < (num_digits / 2); i++) {
		if (x / msd_mask != x % 10) {
			return false;
		}
		x %= msd_mask;
		x /= 10;
		msd_mask /= 100;
	}
	return true;
}
int main() {
	return 0;
}