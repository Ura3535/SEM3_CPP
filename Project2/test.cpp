#include "header.h"
#include <execution>
#include <chrono>
#include <thread>

using DUR = std::chrono::duration<double>;
auto currTime = std::chrono::high_resolution_clock::now;

bool isEven(LL const& x) { return !(x & 1); };

template <class F>
double duration(F&& f)
{
	auto begin = currTime();
	f();
	auto end = currTime();

	return ((DUR)(end - begin)).count();
}

Test task1(LL* arr, LL n)
{
	Test test{};
	double dur = 0;
	test.title = "Without policy";

	//no_policy
	dur = duration([&](){ std::count_if(arr, arr + n, isEven); });
	test.results.push_back(std::make_pair("no_policy", dur));

	return test;
}

Test task2(LL* arr, LL n)
{
	Test test{};
	double dur = 0;
	test.title = "With policy";

	//sequenced_policy
	dur = duration([&](){ std::count_if(std::execution::seq,		arr, arr + n, isEven); });
	test.results.push_back(std::make_pair("seq", dur));

	//paralel_policy
	dur = duration([&](){ std::count_if(std::execution::par,		arr, arr + n, isEven); });
	test.results.push_back(std::make_pair("par", dur));

	//parallel_unsequenced_policy
	dur = duration([&](){ std::count_if(std::execution::par_unseq,	arr, arr + n, isEven); });
	test.results.push_back(std::make_pair("par_unseq", dur));

	//unsequenced_policy
	dur = duration([&](){ std::count_if(std::execution::unseq,		arr, arr + n, isEven); });
	test.results.push_back(std::make_pair("unseq", dur));

	return test;
}

//my count_if for task3
template <class _Type, class _Pr>
LL count_if(_Type* _First, _Type* _Last, _Pr _Pred, int K = 1)
{
	std::vector<LL> res(K);
	LL n = _Last - _First
		, step = (n - 1) / K + 1
		, i = 0;
	std::vector<std::thread> threads;

	for (; (i + 1) * step < n; ++i)
		threads.emplace_back([&]()
			{ res[i] = std::count_if(_First + (i * step), _First + ((i + 1) * step), _Pred); }
		);
	threads.emplace_back([&]()
		{ res[i] = std::count_if(_First + (i * step), _Last, _Pred); }
	);
	for (auto& thread : threads)
		thread.join();

	return std::accumulate(res.begin(), res.end(), 0ll);
}

Test task3(LL* arr, LL n)
{
	Test test{};
	double dur = 0;
	test.title = "Division into threads";

	for (int K = 1; K != 101; ++K) {
		dur = duration([&]() { count_if(arr, arr + n, isEven, K); });
		test.results.push_back(std::make_pair(std::to_string(K), dur));
	}

	return test;
}