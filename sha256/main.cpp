#include <iostream>
#include <fstream>
#include <vector>

#include "sha256.h"
#include "find_prefix.hpp"

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

	// Task 2
	// find_prefix("give my friend 2 bitcoins for a pizza");

	// Task 5
	// sha256 task5_sha256;
	// std::cout << "\nTask 5 hash: " << task5_sha256.hash("give my friend 2 bitcoins for a pizza") << '\n';
	/*
		Signing a result:

		1. echo "<hash>" | xxd -r -p > hash_result.bin

		2. openssl pkeyutl -sign -inkey server.key \
			-in hash_result.bin -out signed.bin \
			-pkeyopt digest:sha256 -pkeyopt rsa_padding_mode:pss -pkeyopt rsa_pss_saltlen:-1


		Verifying a result (should return "Signature Verified Successfully):

		openssl pkeyutl -verify \
			-pubin -inkey <(openssl rsa -in server.key -pubout) \
			-in hash_result.bin -sigfile signed.bin \
			-pkeyopt digest:sha256 -pkeyopt rsa_padding_mode:pss -pkeyopt rsa_pss_saltlen:-1
	*/

	// Task 8
	sha256 task8_sha256;
	std::ifstream file("../kse.der", std::ios::binary);
	if (!file) {
		std::cerr << "kse.der was not found\n";
		return 1;
	}

	std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(file), {});
	file.close();

	std::string buffer_binary(buffer.begin(), buffer.end());
	std::string hash = task8_sha256.hash(buffer_binary);
	std::cout << "Task 8 hash: " << hash << "\n";

	return 0;
}
