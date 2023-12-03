#pragma once
#include "Deck.h"
#include <map>
#include <vector>


std::map<int, int> getStacksOfCards(Deck&, int);
std::map<int, double> inPercentage(const std::map<int, int>&);
std::vector<int> frequent(const std::map<int, int>&);
double average(const std::map<int, int>&);
double median(const std::map<int, int>&);