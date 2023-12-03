#pragma once

#include "common.h"

namespace get_test
{
    namespace fs = std::filesystem;

    std::vector<test_t> get_tests(const fs::path& directory);
}