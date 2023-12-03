//compiler: MVSC v143 - VS 2022 C++ x64/x86
//standard: ISO C++20

#include <iostream>
#include <iomanip>	//setpresision
#include "Deck.h"
#include "Func.h"

int main() {
	std::cout << std::fixed << std::setprecision(6);
	try {
		int numCards = 0, n = 0;
		std::cout << "Enter the number of cards and how many cards to deal: ";
		if (!(std::cin >> numCards >> n) || n <= 0)
			throw 1;
		Deck deck(numCards);	//0 < numCards
		if (deck.isInvalid())
			throw 1;
		std::map<int, int> stacks = getStacksOfCards(deck, n);
		std::cout << "\n--------------------\n";
		//in percentage
		std::cout << "In Percentage:";
		for (const auto& x : inPercentage(stacks))
			std::cout << '\n' << x.first << " : " << x.second << '%';
		std::cout << "\n--------------------\n";
		//frequent
		std::cout << "Frequent: ";
		for (const auto& x : frequent(stacks))
			std::cout << x << ' ';
		std::cout << "\n--------------------\n";
		//average
		std::cout << "Average: " << average(stacks);
		std::cout << "\n--------------------\n";
		//median
		std::cout << "Median: " << median(stacks);
		std::cout << "\n--------------------\n";
	}
	catch (...) {
		std::cout << "Error\n";
		return 1;
	}
	return 0;
}