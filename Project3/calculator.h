#pragma once

#include <vector>
#include <queue>
#include <mutex>
#include <atomic>

enum SetNames {
	A, B, C, D, E, F, G, H, I, J
};

struct Set {
	int actions = 0;
	std::atomic_int curr_action = 0;
	std::atomic_int done_actions = 0;
	std::atomic_int access = 0;
	std::vector<SetNames> inaccessibles{};

	Set() = default;
	Set(const Set&) = delete;
	Set& operator=(const Set&) = delete;

	Set(int actions, int access, std::vector<SetNames> inaccessibles);
	Set(Set&&);
};

class Calculator {
public:
	Calculator();

	void start();
private:
	void calculate();
	bool is_done();
	std::pair<SetNames, int> get_next_action();
	void finish_calculation(SetNames);

	std::vector<Set> sets;
	std::queue<SetNames> order;
	SetNames current;
	std::mutex mutex_get_action;
};