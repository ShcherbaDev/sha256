#pragma once
#include <string>
#include <cstdint>

class sha256 {
public:
	sha256();
	std::string hash(const std::string& message);
private:
	uint32_t H[8]; // Hash
	void process_block(const unsigned char* block);
};
