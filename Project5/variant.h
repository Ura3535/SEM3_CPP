#pragma once

#include <vector>
#include <string>
#include <chrono>

namespace execution_time
{
	using namespace std::chrono_literals;
	const auto slow = 7s;
	const auto fast = 1s;
}

namespace variant_8
{
	enum Ñalculations
	{
		A, B1, B2, B3, C1, C2, D
	};
	const size_t calc_enum_size = 7;

	std::string to_string(Ñalculations X) {
		switch (X)
		{
		case A:		return "A";
		case B1:	return "B1";
		case B2:	return "B2";
		case B3:	return "B3";
		case C1:	return "C1";
		case C2:	return "C2";
		case D:		return "D";
		}
	}

	const std::vector<Ñalculations> slow_execution{ B1, C2 };
	const std::vector<Ñalculations> dependences[calc_enum_size]{
	/*A */	{},
	/*B1*/	{A },
	/*B2*/	{},
	/*B3*/	{},
	/*C1*/	{B1, B2, B3},
	/*C2*/	{},
	/*D */	{C1, C2}
	};
	const std::vector<std::vector<Ñalculations>> order{
		{A , B1, C1, D },
		{B2, B3, C2}
	};
}
