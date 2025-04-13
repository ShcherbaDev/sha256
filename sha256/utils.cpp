#include "utils.h"

// 2.2.2 (ROTR)
uint32_t utils::right_rotate(uint32_t value, unsigned int count) {
	return (value >> count) | (value << (32 - count));
}

// 4.1.2 (4.2)
uint32_t utils::Ch(uint32_t x, uint32_t y, uint32_t z) {
	return (x & y) ^ (~x & z);
}

// 4.1.2 (4.3)
uint32_t utils::Maj(uint32_t x, uint32_t y, uint32_t z) {
	return (x & y) ^ (x & z) ^ (y & z);
}

// 4.1.2 (4.4)
uint32_t utils::Sigma0(uint32_t x) {
	return right_rotate(x, 2) ^ right_rotate(x, 13) ^ right_rotate(x, 22);
}

// 4.1.2 (4.5)
uint32_t utils::Sigma1(uint32_t x) {
	return right_rotate(x, 6) ^ right_rotate(x, 11) ^ right_rotate(x, 25);
}

// 4.1.2 (4.6)
uint32_t utils::sigma0(uint32_t x) {
	return right_rotate(x, 7) ^ right_rotate(x, 18) ^ (x >> 3);
}

// 4.1.2 (4.7)
uint32_t utils::sigma1(uint32_t x) {
	return right_rotate(x, 17) ^ right_rotate(x, 19) ^ (x >> 10);
}
