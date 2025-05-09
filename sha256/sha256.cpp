#include "sha256.h"

#include <iomanip>
#include <sstream>
#include <vector>

#include "utils.h"

// SHA-256
// Message size (bits): < 2^64
// Block size (bits): 512
// Word size: 32
// Message digest size (bits): 256

// 4.2.2 - SHA-256 Constants
const uint32_t K[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

sha256::sha256() {}

std::string sha256::hash(const std::string& message) {
	// 5.3.3 - Initial hash value
	H[0] = 0x6a09e667;
	H[1] = 0xbb67ae85;
	H[2] = 0x3c6ef372;
	H[3] = 0xa54ff53a;
	H[4] = 0x510e527f;
	H[5] = 0x9b05688c;
	H[6] = 0x1f83d9ab;
	H[7] = 0x5be0cd19;

	// 5.2 - Padding the message
	uint64_t bit_length = message.size() * 8;

	// Calculate padding length
	std::vector<unsigned char> padded_message(message.begin(), message.end());
	padded_message.push_back(0x80);
	while ((padded_message.size() % 64) != 56) {
		padded_message.push_back(0);
	}

	// Append length of message as 64bit big-endian integer
	for (int i = 7; i >= 0; i--) {
		padded_message.push_back((bit_length >> (i * 8)) & 0xFF);
	}

	// Process each 512-bit block
	for (size_t i = 0; i < padded_message.size(); i += 64) {
		process_block(&padded_message[i]);
	}

	std::stringstream stringstream;
	for (int i = 0; i < 8; i++) {
		stringstream << std::hex << std::setw(8) << std::setfill('0') << H[i];
		// stringstream << std::hex << H[i];
	}
	return stringstream.str();
}

void sha256::process_block(const unsigned char* block) {
	uint32_t W[64];
	uint32_t a, b, c, d, e, f, g, h;

	// 6.2.2 (1) Prepare message schedule
	for (int t = 0; t < 16; t++) {
		W[t] = (block[t * 4] << 24) | (block[t * 4 + 1] << 16) | (block[t * 4 + 2] << 8) | (block[t * 4 + 3]);
	}

	for (int t = 16; t < 64; t++) {
		W[t] = utils::sigma1(W[t-2]) + W[t-7] + utils::sigma0(W[t-15]) + W[t-16];
	}

	// 6.2.2 (2) Initialize working variables
	a = H[0];
	b = H[1];
	c = H[2];
	d = H[3];
	e = H[4];
	f = H[5];
	g = H[6];
	h = H[7];

	// 6.2.2 (3) Main loop
	for (int t = 0; t < 64; t++) {
		uint32_t temp1 = h + utils::Sigma1(e) + utils::Ch(e, f, g) + K[t] + W[t];
		uint32_t temp2 = utils::Sigma0(a) + utils::Maj(a, b, c);
		h = g;
		g = f;
		f = e;
		e = d + temp1;
		d = c;
		c = b;
		b = a;
		a = temp1 + temp2;
	}

	// 6.2.2 (4) Update hash values
	H[0] += a;
	H[1] += b;
	H[2] += c;
	H[3] += d;
	H[4] += e;
	H[5] += f;
	H[6] += g;
	H[7] += h;
}
