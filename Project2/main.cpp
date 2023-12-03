//compiler: MVSC v143 - VS 2022 C++ x64/x86
//standard: ISO C++20
//CPU: Intel Core i5-11400H (12 threads)
//Variant: 4

#include "header.h"
#include <iostream>

int main()
{
    LL n = (1ll << 25); // 2^25
    LL count = 0;
    LL* arr = new LL[n];
    for (LL i = 0; i != n; ++i) arr[i] = i;

    Output out("D:\\result.html");
    out.outputTestInTable(task1(arr, n));
    std::cerr << "task1 complete\n";
    out.outputTestInTable(task2(arr, n));
    std::cerr << "task2 complete\n";
    out.outputTestInTable(task3(arr, n));
    std::cerr << "task3 complete\n";

    delete[] arr;
}