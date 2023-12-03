#include "initialize.h"

namespace variant_16
{
	std::vector<Set> fill_sets()
	{
		std::vector<Set> sets{};
		
		sets.push_back(Set(7, 0, std::vector<SetNames>{SetNames::B, SetNames::C, SetNames::D})	);	//A
		sets.push_back(Set(6, 1, std::vector<SetNames>{SetNames::E})				);	//B
		sets.push_back(Set(5, 1, std::vector<SetNames>{SetNames::F, SetNames::G})		);	//C
		sets.push_back(Set(6, 1, std::vector<SetNames>{SetNames::H})				);	//D
		sets.push_back(Set(4, 1, std::vector<SetNames>{SetNames::I})				);	//E
		sets.push_back(Set(7, 1, std::vector<SetNames>{SetNames::I})				);	//F
		sets.push_back(Set(5, 1, std::vector<SetNames>{SetNames::J})				);	//G
		sets.push_back(Set(5, 1, std::vector<SetNames>{SetNames::J})				);	//H
		sets.push_back(Set(8, 2, std::vector<SetNames>{})					);	//I
		sets.push_back(Set(5, 2, std::vector<SetNames>{})					);	//G

		return sets;
	}

	std::queue<SetNames> fill_order()
	{
		return std::queue<SetNames>({ SetNames::A, SetNames::B, SetNames::C, SetNames::D, SetNames::E, SetNames::F, SetNames::G, SetNames::H, SetNames::I, SetNames::J });
	}
}