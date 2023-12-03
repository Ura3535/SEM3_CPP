#include "Deck.h"
#include <random>

//class Card
void Card::set(int n, char s)
{
	num = n;
	suit = s;
}

std::partial_ordering Card::operator<=>(const Card& other) const
{
	return (num == other.num
		? std::partial_ordering::equivalent
		: (num < other.num
			? std::partial_ordering::less
			: std::partial_ordering::greater));
}

/*
std::ostream& operator<<(std::ostream& os, const Card& obj)
{
	os << obj.num << obj.suit;
	return os;
}
*/

//class Deck
void Deck::shuffle()
{
	std::random_device r;
	std::seed_seq seeds{ r(), r(), r(), r(), r(), r() };
	std::default_random_engine e(seeds);
	std::shuffle(deck, deck + len, e);
}

Deck::Deck(int n)
{
	if (n <= 0) {	//INVALID_DECK
		pos = len = 0;
		deck = nullptr;
	}
	else {
		pos = len = 4 * (size_t)n;
		deck = new Card[len];
		for (int i = 0; i != n; ++i) {
			deck[i * 4    ].set(i, 3);	//i♥
			deck[i * 4 + 1].set(i, 4);	//i♦
			deck[i * 4 + 2].set(i, 5);	//i♣
			deck[i * 4 + 3].set(i, 6);	//i♠
		}
		shuffle();
	}
}

Deck::~Deck()
{
	delete[] deck;
}

bool Deck::isInvalid() const
{
	return len == 0;
}

Card Deck::operator()()
{
	if (pos == 0) {
		shuffle();
		pos = len;
	}
	return deck[--pos];
}
