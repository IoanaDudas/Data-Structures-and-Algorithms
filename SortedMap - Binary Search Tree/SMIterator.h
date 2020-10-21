#pragma once
#include "SortedMap.h"
#include <stack>

using namespace std;

//DO NOT CHANGE THIS PART
class SMIterator{
	friend class SortedMap;
private:
	const SortedMap& map;
	SMIterator(const SortedMap& mapionar);

    BST bst;
    stack<int> stack;
    int currentElement;

public:
	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;
};

