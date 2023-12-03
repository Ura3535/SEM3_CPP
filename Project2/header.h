#pragma once

#include <string>
#include <vector>
#include <fstream>

using LL = long long;

struct Test {
	std::string title;
	std::vector<std::pair<std::string, double>> results;
};

Test task1(LL* arr, LL n);
Test task2(LL* arr, LL n);
Test task3(LL* arr, LL n);

//Output of all results in HTML as tables
class Output
{
	std::ofstream out;

public:
	Output(std::string);
	~Output();
	void outputTestInTable(const Test&);
};