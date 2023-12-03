#include "variant.h"
#include <future>
#include <atomic>
#include <iostream>
#include <syncstream>
#include <algorithm>

namespace vr = variant_8;
namespace ch = std::chrono;
auto currTime = ch::high_resolution_clock::now;

static void calculate(vr::Ñalculations calc)
{
	std::osyncstream(std::cout) << "Calculate the " << to_string(calc) << " in " << std::this_thread::get_id() << " thread\n";

	if (std::find(vr::slow_execution.begin(), vr::slow_execution.end(), calc) != vr::slow_execution.end())
		std::this_thread::sleep_for(execution_time::slow);
	else
		std::this_thread::sleep_for(execution_time::fast);

	std::osyncstream(std::cout) << "Calculation of " << to_string(calc) << " completed\n";
}

void work()
{
	std::cout << "main thread: " << std::this_thread::get_id() << "\n\n";

	std::atomic_bool done[vr::calc_enum_size]{};
	std::vector<std::future<void>> futures;
	auto parallel_calculate = [](std::atomic_bool* done, const std::vector<vr::Ñalculations>& sequence){
		for (const auto& calc : sequence) {
			while (std::any_of(
				vr::dependences[(int)calc].begin(),
				vr::dependences[(int)calc].end(),
				[&done](vr::Ñalculations i) { return !done[(int)i].load(); }
			)); //active waiting

			calculate(calc);
			done[(int)calc].store(true);
		}
	};

	auto begin = currTime();
	if(!vr::order.empty())
	{
		futures.push_back(std::async(std::launch::deferred, parallel_calculate, done, *vr::order.begin()));

		for (auto it = vr::order.begin() + 1; it != vr::order.end(); ++it)
			futures.push_back(std::async(std::launch::async, parallel_calculate, done, *it));

		for (const auto& future : futures)
			future.wait();
	}
	auto end = currTime();

	std::cout << "\nExecution time: " << ch::duration_cast<ch::milliseconds>(end - begin) << '\n';
}