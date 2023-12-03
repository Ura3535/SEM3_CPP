#include <iostream>
#include <syncstream>
#include <thread>
#include "test_execution.h"
#include "my_struct.h"

namespace test_execution
{
    auto currTime = ch::high_resolution_clock::now;

    static void execute_test(const test_t& commands, MyStruct& obj)
    {
        for (const auto& command : commands.second) {
            switch (command.command)
            {
            case RWS::READ:
                obj.get(command.arg1);
                break;
            case RWS::WRITE:
                obj.set(command.arg1, command.arg2);
                break;
            case RWS::STRING:
                (std::string)obj;
                break;
            default:
                throw std::logic_error("Uncertain command");
            }
        }
    }

    ch::milliseconds execute_all_tests(const std::vector<test_t>& comands_sets, int thread_num)
    {
        std::vector<std::thread> threads;
        MyStruct my_struct;
        std::mutex mutex;
        auto curr_test = comands_sets.begin();

        auto begin = currTime();
        for (int i = 0; i < thread_num; ++i)
            threads.emplace_back([&]() {
                while (true)
                {
                    mutex.lock();
                    if (curr_test == comands_sets.end()) {
                        mutex.unlock();
                        break;
                    }
                    const auto& test = *curr_test;
                    ++curr_test;
                    mutex.unlock();

                    auto _begin = currTime();
                    execute_test(test, my_struct);
                    auto _end = currTime();

                    std::osyncstream(std::cout) << test.first << " | Executed (" << (ch::duration_cast<ch::milliseconds>(_end - _begin)) << ")\t|\n";
                }
            });
        for (auto& thread : threads)
            thread.join();
        auto end = currTime();

        return ch::duration_cast<ch::milliseconds>(end - begin);
    }
}