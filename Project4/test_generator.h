#pragma once

#include <filesystem>
#include "frequencies.h"

namespace test_generator
{
	namespace fs = std::filesystem;

	void create_tests(const fs::path& directory, int len, long id = 0);
}