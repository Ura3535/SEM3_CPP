#include "calculator.h"
#include "initialize.h"
#include <thread>
#include <iostream>
#include <syncstream>

using namespace variant_16;
auto currTime = std::chrono::high_resolution_clock::now;

void f(SetNames set, int action)
{
	std::this_thread::sleep_for(action_execution_time);
	std::osyncstream(std::cout) 
		<< "In " << std::this_thread::get_id()
		<< " thread\tfrom the set " << (char)(set + 'A') 
		<< " action " << action + 1
		<< " is executed." << std::endl;
}

//struct Task
Set::Set(int actions, int access, std::vector<SetNames> inaccessibles)
	: actions(actions)
	, curr_action(0)
	, done_actions(0)
	, access(access)
	, inaccessibles(inaccessibles)
{}

Set::Set(Set&& other)
	: actions(other.actions)
	, curr_action(other.curr_action.load())
	, done_actions(other.done_actions.load())
	, access(other.access.load())
	, inaccessibles(std::move(other.inaccessibles))
{}

//class Calculator
Calculator::Calculator()
	: sets(fill_sets())
	, order(fill_order())
{
	current = order.front();
	order.pop();
}

void Calculator::start()
{
	std::vector<std::thread> threads;

	auto begin = currTime();
	for (int i = 0; i != nt; ++i)
		threads.emplace_back( [&](){ calculate(); });
	for (auto& thread : threads)
		thread.join();
	auto end = currTime();
	
	std::cout << "\nExecution time: " << ((std::chrono::duration_cast<std::chrono::milliseconds>)(end - begin)).count() << "ms\n";
	std::cout << "Expected time to complete all actions: " << expected_execution_time.count() << "ms\n";
}

void Calculator::calculate()
{
	std::osyncstream(std::cout) << "Thread " << std::this_thread::get_id() << " start" << std::endl;

	while (true) {
		mutex_get_action.lock();
		if (is_done()) {
			mutex_get_action.unlock();
			break;
		}
		auto task = get_next_action();
		mutex_get_action.unlock();

		f(task.first, task.second);
		finish_calculation(task.first);
	}

	std::osyncstream(std::cout) << "Thread " << std::this_thread::get_id() << " finish " << std::endl;
}

bool Calculator::is_done()
{
	return sets[current].curr_action.load() == sets[current].actions
		&& order.empty();
}

std::pair<SetNames, int> Calculator::get_next_action()
{
	if (sets[current].curr_action.load() == sets[current].actions) {
		if (order.empty()) throw std::out_of_range("No available tasks");
		current = order.front();
		order.pop();
	}
	while (sets[current].access.load() != 0)
		std::this_thread::sleep_for(std::min(10ms, action_execution_time / 10));
	auto res = std::make_pair(current, sets[current].curr_action.load());
	++sets[current].curr_action;

	return res;
}

void Calculator::finish_calculation(SetNames set)
{
	++sets[set].done_actions;
	if (sets[set].done_actions.load() == sets[set].actions) {
		for (auto& inaccessible_set : sets[set].inaccessibles)
			--sets[inaccessible_set].access;
	}
}