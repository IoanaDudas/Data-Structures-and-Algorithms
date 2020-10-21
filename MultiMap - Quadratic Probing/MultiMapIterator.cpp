#include "MultiMapIterator.h"
#include "MultiMap.h"

// best case = Theta(capacity), worst case = Theta(capacity), average case = Theta(capacity)
MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
    this->current = 0;

    for(int i = 0; i < c.capacity; ++i)
    {
        if(c.DynamicVector[i].first != -11111 and c.DynamicVector[i].first != -111111)
        {
            TElem e = c.DynamicVector[i];
            this->elements.push_back(e);
        }
    }
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1)
TElem MultiMapIterator::getCurrent() const{
    if(valid())
        return this->elements[this->current];
    throw exception();
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1)
bool MultiMapIterator::valid() const {
	if(this->current < this->elements.size())
	    return true;
	return false;
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1)
void MultiMapIterator::next() {
    if(!valid())
        throw exception();
    this->current++;
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1)
void MultiMapIterator::first() {
	this->current = 0;
}

