#include "initialize.h"

namespace variant_16
{
	std::vector<Set> fill_sets()
	{
		std::vector<Set> sets{};
		
		/*A*/	sets.push_back(Set(7, 0, std::vector<SetNames>{B, C, D}));
		/*B*/	sets.push_back(Set(6, 1, std::vector<SetNames>{E}));
		/*C*/	sets.push_back(Set(5, 1, std::vector<SetNames>{F, G}));
		/*D*/	sets.push_back(Set(6, 1, std::vector<SetNames>{H}));
		/*E*/	sets.push_back(Set(4, 1, std::vector<SetNames>{I}));
		/*F*/	sets.push_back(Set(7, 1, std::vector<SetNames>{I}));
		/*G*/	sets.push_back(Set(5, 1, std::vector<SetNames>{J}));
		/*H*/	sets.push_back(Set(5, 1, std::vector<SetNames>{J}));
		/*I*/	sets.push_back(Set(8, 2, std::vector<SetNames>{}));
		/*J*/	sets.push_back(Set(5, 2, std::vector<SetNames>{}));

		return sets;
	}

	std::queue<SetNames> fill_order()
	{
		return std::queue<SetNames>({ A, B, C, D, E, F, G, H, I, J });
	}
}