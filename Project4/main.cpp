//compiler: MVSC v143 - VS 2022 C++ x64/x86
//standard: ISO C++20
//CPU: Intel Core i5-11400H (12 threads)
//Variant: 12

#include <iostream>
#include <filesystem>
#include "test_generator.h"
#include "get_test.h"
#include "test_execution.h"

namespace fs = std::filesystem;

void print_results(const std::vector<test_t>&  data, int thread_num)
{
    std::cout << "\n<-----------------------------|Testing-in-" << thread_num << "-threads|----------------------------->\n";

    auto time = test_execution::execute_all_tests(data, thread_num);
    
    std::cout << "<-------------------------|Total execution time: " << time << "|------------------------->\n";
}

int main()
{
    const fs::path directory("D:\\Tests");
    const int command_num = 100000;
    const long test_num = 6;

    for(long id = 0; id != test_num; ++id)
        test_generator::create_tests(directory, command_num, id);
    
    const auto data = get_test::get_tests(directory);

    print_results(data, 1);
    print_results(data, 2);
    print_results(data, 3);

}