#pragma once
#include <fstream>


struct Card
{
	int num;
	char suit;

	void set(int, char);
	std::partial_ordering operator<=>(const Card&) const;
	//friend std::ostream& operator<<(std::ostream&, const Card&); //was needed to check for errors
};

class Deck
{
	Card* deck;
	size_t len, pos;

	void shuffle();
public:
	Deck(int);
	~Deck();
	bool isInvalid() const;
	Card operator()();
};