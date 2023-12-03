#include <random>
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include "test_generator.h"

namespace test_generator
{
	static int generate_int_from_1_to_n(int n)
	{
		std::random_device r;
		std::seed_seq seeds{ r(), r(), r(), r(), r(), r() };
		std::default_random_engine e(seeds);
		std::uniform_int_distribution<int> distribution(1, n);

		return distribution(e);
	}

	static std::string generate_command(const frequencies::Frequencies& freq)
	{
		int random = generate_int_from_1_to_n(freq.sum());

		random -= freq.field_0_read;
		if (random <= 0) return "read 0";

		random -= freq.field_0_write;
		if (random <= 0) return "write 0 1";

		random -= freq.field_1_read;
		if (random <= 0) return "read 1";

		random -= freq.field_1_write;
		if (random <= 0) return "write 1 1";

		random -= freq.field_2_read;
		if (random <= 0) return "read 2";

		random -= freq.field_2_write;
		if (random <= 0) return "write 2 1";

		random -= freq.string;
		if (random <= 0) return "string";

		throw std::logic_error("Sum of frequencies does not meet expectations");
	}

	void create_tests(const fs::path& directory, int len, long id)
	{
		struct Test
		{
			const fs::path path;
			const std::string description;
			const frequencies::Frequencies& freq;
		};

		const std::string file_name("Test" + std::to_string(id));
		const std::string command_num(std::to_string(len) + " commands");
		const std::vector<Test> tests{
			{directory / (file_name + "_A.txt"), file_name + "_A (frequencies from the variant)\twith "	+ command_num, frequencies::variant_12},
			{directory / (file_name + "_B.txt"), file_name + "_B (equal frequencies)\t\twith "			+ command_num, frequencies::equal},
			{directory / (file_name + "_C.txt"), file_name + "_C (my frequencies)\t\twith "				+ command_num, frequencies::my_freq}
		};
		std::vector<std::thread> threads;

		for (auto const& test : tests)
			threads.emplace_back([&]() {
				std::ofstream file(test.path);
				file << test.description << '\n';
				for (int i = 0; i < len; ++i)
					file << generate_command(test.freq) << '\n';
			});
		for (auto& thread : threads)
			thread.join();

		std::cerr << "created tests with id = " << id << '\n';
	}
}