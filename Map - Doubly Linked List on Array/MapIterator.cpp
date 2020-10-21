#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;

// best case = Theta(1), worst case = Theta(1), average case = Theta(1), O(1)
MapIterator::MapIterator(const Map& d) : map(d)
{
    this->currentElement = d.map.head;
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1), O(1)
void MapIterator::first() {
    this->currentElement = this->map.map.head;
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1), O(1)
void MapIterator::next() {
    if(!valid())
        throw exception();
    this->currentElement = this->map.map.nodes[this->currentElement].next;
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1), O(1)
TElem MapIterator::getCurrent(){
    if(!valid())
        throw exception();
    return this->map.map.nodes[this->currentElement].data;
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1), O(1)
bool MapIterator::valid() const {
    if(this->currentElement != -1)
        return true;
	return false;
}



