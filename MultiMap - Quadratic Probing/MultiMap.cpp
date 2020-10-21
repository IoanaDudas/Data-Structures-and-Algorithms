#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

// best case = Theta(1), worst case = Theta(1), average case = Theta(1)
bool prime(int nr)
{
    if (nr == 1 or nr == 0)
        return false;
    if (nr == 2)
        return true;

    for(int div = 2; div <= nr/2; div++)
        if(nr % div == 0)
            return false;
    return true;
}
// best case = Theta(capacity), worst case = Theta(capacity), average case = Theta(capacity)
MultiMap::MultiMap() {
	this->capacity = CAPACITY;
	this->DynamicVector = new TElem[this->capacity];
	this->length = 0;
	this->maxFactor = 5;
	for(int i = 0; i <= this->capacity; i++)
	    this->DynamicVector[i] = NULL_TELEM;
}

// best case = Theta(1), worst case = Theta(capacity^2), average case = Theta(1)
void MultiMap::add(TKey c, TValue v) {
    int index = hash(c, 0);

    if (this->DynamicVector[index].first == -11111 or this->DynamicVector[index].first == -111111)
    {
        this->DynamicVector[index] = TElem(c, v);
        this->length++;
    }
    else
    {
        int i = 1;
        int index2 = hash(c, i);
        while(this->DynamicVector[index2].first != -11111 and this->DynamicVector[index2].first != -111111)
        {
            ++i;
            index2 = hash(c, i);
        }
        this->DynamicVector[index2] = TElem(c, v);
        this->length++;
        if(i >= this->maxFactor)
            resize();
    }
    if(this->length >= this->capacity)
        resize();
}

// best case = Theta(1), worst case = O(capacity), average case = Theta(1)
bool MultiMap::remove(TKey c, TValue v) {
    int index = hash(c, 0);

    if(this->DynamicVector[index].first == c and this->DynamicVector[index].second == v)
    {
        this->DynamicVector[index].first = -111111;
        this->length--;
        return true;
    }
    else
    {
        int i = 1;
        int index2 = hash(c, i);
        while(this->DynamicVector[index2].first != -11111)
        {
            if(this->DynamicVector[index2].first == c and this->DynamicVector[index2].second == v)
            {
                this->DynamicVector[index2].first = -111111;
                this->length--;
                return true;
            }
            ++i;
            index2 = hash(c, i);
        }
        if(this->DynamicVector[index2].first == c and this->DynamicVector[index].second == v)
        {
            this->DynamicVector[index2].first = -111111;
            this->length--;
            return true;
        }
        return false;
    }

}

// best case = Theta(1), worst case = O(capacity), average case = Theta(1)
vector<TValue> MultiMap::search(TKey c) const {
    int index = hash(c, 0);
    vector<TValue> valuesVector;

    if(this->DynamicVector[index].first == c)
        valuesVector.push_back(this->DynamicVector[index].second);
    int i = 1;
    int index2 = hash(c, i);
    while (this->DynamicVector[index2].first != -11111)
    {
        if (this->DynamicVector[index2].first == c)
            valuesVector.push_back(this->DynamicVector[index2].second);
        ++i;
        index2 = hash(c, i);
    }
	return valuesVector;
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1)
int MultiMap::size() const {
	if(isEmpty())
	    return 0;
	return this->length;
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1)
bool MultiMap::isEmpty() const {
	if(this->length == 0)
	    return true;
	return false;
}

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1)
MultiMap::~MultiMap() {
    delete[] this->DynamicVector;
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1)
int MultiMap::hash(TKey k, int i) const {
    return (abs(k) % this->capacity + hashI(i)) % capacity;
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1)
int MultiMap::hashI(int i) const {
    return 0.5 * i + 0.5 * i * i;
}

// best case = Theta(capacity^2), worst case = Theta(capacity^2), average case = Theta(capacity^2)
void MultiMap::resize(){
    int oldCapacity = capacity;
    capacity = capacity * capacity;

    while(!prime(capacity))
        --capacity;

    TElem* newDynamicVector = this->DynamicVector;

    this->DynamicVector = new TElem[capacity];
    this->maxFactor = this->maxFactor * this->maxFactor;

    for(int i = 0; i <= this->capacity; i++)
        this->DynamicVector[i] = NULL_TELEM;

    this->length = 0;

    for(int index = 0; index < oldCapacity; ++index)
    {
        if(newDynamicVector[index].first != -11111 and newDynamicVector[index].first != -111111)
        {
            TElem elem = newDynamicVector[index];
            add(elem.first, elem.second);
        }
    }
    //delete[] newDynamicVector;
}

// best case = Theta(capacity), worst case = Theta(capacity), average case = Theta(capacity)
void MultiMap::filter(Condition cond)
{
    for(int i = 0; i <= this->capacity; i++)
    {
        if(this->DynamicVector[i].first != -11111 and this->DynamicVector[i].first != -111111)
            if(!cond(this->DynamicVector[i].second))
            {
                this->length--;
                this->DynamicVector[i].first = -111111;
            }
    }
}

