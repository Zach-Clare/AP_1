#pragma once

#include "Item.h"
#include <vector>


class ItemList
{
public:
	std::vector<Item*> items;
	std::vector<char> type_codes;
	void add(Item*, char);
	void remove(int);
};

