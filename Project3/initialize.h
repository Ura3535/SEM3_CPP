#pragma once

#include "calculator.h"

using namespace std::chrono_literals;

namespace variant_16
{
	const auto action_execution_time = 500ms;
	const auto expected_execution_time = action_execution_time * 13;
	const int nt = 5;
	std::vector<Set> fill_sets();
	std::queue<SetNames> fill_order();
}
