#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
    currentElement = 0;
}

void SMIterator::first(){
	currentElement = 0;
}

void SMIterator::next(){
	if(!valid())
	    throw exception();
	currentElement++;
}

bool SMIterator::valid() const{
	if(currentElement < map.numberOfElements)
        return true;
	return false;
}

TElem SMIterator::getCurrent() const{
	if(valid())
	    return map.map[currentElement];
	throw  exception();
	//return NULL_TPAIR;
}


