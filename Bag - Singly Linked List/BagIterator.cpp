#include <exception>
#include "BagIterator.h"
#include "Bag.h"
#include <iostream>

using namespace std;

// best case = Theta(1), worst case = Theta(1), average case = Theta(1), O(1)
BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->currentNode = c.bagSll->head;
    this->frequency = 1;
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1), O(1)
void BagIterator::first() {
    this->currentNode = bag.bagSll->head;
    this->frequency = 1;
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1), O(1)
void BagIterator::next() {
    if(!valid())
        throw exception();
    if(this->frequency < this->currentNode->frequency)
    {
        this->frequency++;
        return;
    }
	this->currentNode = this->currentNode->next;
    this->frequency = 1;
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1), O(1)
bool BagIterator::valid() const {
	if(currentNode == NULL)
	    return false;
    return true;
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1), O(1)
TElem BagIterator::getCurrent() const
{
	if(valid())
        return currentNode->data;
	throw exception();
}
