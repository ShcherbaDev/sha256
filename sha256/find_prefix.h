#pragma once
#include <iomanip>
#include <iostream>
#include <mutex>
#include <random>
#include <string>

#include "sha256.h"

// Завдання 2:
// Пiдберiть префiкс з довжиною 20 байтiв
// до повiдомлення «give my friend 2 bitcoins for a pizza» (текстове повiдомлення),
// щоб геш-значення утвореного рядка (конкатенацiя префiксу та повiдомлення)
// починалося з 32 нулiв (у бiтовому представленнi).

inline std::atomic<bool> is_found {false};
inline std::mutex mutex;

inline std::string generate_random_prefix(size_t size, std::mt19937& rng, std::uniform_int_distribution<int>& dist) {
	std::string result;

	for (size_t i = 0; i < size; i++) {
		result += static_cast<char>(dist(rng));
	}

	return result;
}

inline void worker(const std::string& input, int thread_id) {
	static thread_local std::mt19937 rng(std::random_device{}() ^ std::hash<std::thread::id>()(std::this_thread::get_id()));
	static thread_local std::uniform_int_distribution<int> dist(0, 255);

	sha256 sha256;

	while (!is_found.load()) {
		std::string prefix = generate_random_prefix(20, rng, dist);
		std::string combined = prefix + input;
		std::string hash = sha256.hash(combined);

		if (hash.substr(0, 8) == "00000000") {
			is_found = true;

			std::lock_guard<std::mutex> lock(mutex);
			std::cout << "Thread #" << thread_id << " found prefix " << prefix << '\n';
			for (unsigned char c : prefix) {
				std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)c;
			}
			std::cout << "\nHash: " << hash << '\n';

			break;
		}

		// std::lock_guard<std::mutex> lock(mutex);
		// std::cout << "Wrong: " << hash << '\n';
	}
}

inline void find_prefix(const std::string& input, int number_of_threads) {
	std::vector<std::thread> threads;

	for (int i = 0; i < number_of_threads; i++) {
		threads.emplace_back(worker, std::cref(input), i);
	}

	for (auto& thread : threads) {
		thread.join();
	}
}
