#include <iostream>

#include "sha256.h"

void assert(int test_index, std::string input, std::string expected_output) {
	sha256 sha256;
	if (sha256.hash(input) != expected_output) {
		std::cout << "Test #" << test_index << " output does not match the expected value\n";
		return;
	}
	std::cout << "Test #" << test_index << " PASS\n";
}

int main() {
	assert(1, "abc", "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
	assert(2, "", "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
	assert(3, "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1");
	assert(4, "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu", "cf5b16a778af8380036ce59e7b0492370b249b11e8f07a51afac45037afee9d1");
	assert(5, std::string(1000000, 'a'), "cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0");
	return 0;
}
