#pragma once
#include <cstdint>

class utils {
public:
	static uint32_t right_rotate(uint32_t value, unsigned int count);

	static uint32_t Ch(uint32_t x, uint32_t y, uint32_t z);

	static uint32_t Maj(uint32_t x, uint32_t y, uint32_t z);

	static uint32_t Sigma0(uint32_t x);

	static uint32_t Sigma1(uint32_t x);

	static uint32_t sigma0(uint32_t x);

	static uint32_t sigma1(uint32_t x);
};
