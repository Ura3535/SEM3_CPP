#pragma once

#include <chrono>
#include "common.h"

namespace test_execution
{
    namespace ch = std::chrono;
    namespace fs = std::filesystem;

    ch::milliseconds execute_all_tests(const std::vector<test_t>& comands_sets, int thread_num);
}