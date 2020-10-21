#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>
using namespace std;

SortedMap::SortedMap(Relation r) {
    relation = r;
    capacity = 16;
    numberOfElements = 0;
    map = new TElem[capacity];
}

TValue SortedMap::add(TKey k, TValue v) {
    int i;
    TElem newElement;
    newElement.first = k;
    newElement.second = v;

    // check if the key already exists in the map and replace it's value
    // best case = 1, worst case = numberOfElements, average case = numberOfElements
    for (i = 0; i < numberOfElements; i++)
        if (map[i].first == newElement.first)
        {
            int oldValue = map[i].second;
            map[i].second = newElement.second;
            return oldValue;
        }

    // increase the capacity
    if (capacity == numberOfElements)
    {
        TElem* newMap = new TElem[2 * capacity];
        for (i = 0; i < capacity; i++)
        {
            newMap[i] = map[i];
        }
        delete[] map;
        capacity *= 2;
        map = newMap;
    }

    i = 0;
    int found = 0, positionFound = 0;
    // best case = T(1), worst case = T(numberOfElements), average case = T(numberOfElements), O(numberOfElements)
    while (i < numberOfElements)
    {
        if (relation(newElement.first, map[i].first) == false)
            i++;
        else
        {
            found = 1;
            positionFound = i;
            break;
        }
    }
    if (found == 1)
    {
        for (i = numberOfElements; i > positionFound; i--)
            map[i] = map[i - 1];
        numberOfElements++;
        map[positionFound] = newElement;
    }
    else
    {
        map[numberOfElements] = newElement;
        numberOfElements ++;
    }
    return NULL_TVALUE;
}

TValue SortedMap::search(TKey k) const {
    // best case = T(1), worst case = T(numberOfElements), average case = T(numberOfElements), O(numberOfElements)
    for (int i = 0; i < numberOfElements; i++)
        if (map[i].first == k)
            return map[i].second;
    return NULL_TVALUE;
}

TValue SortedMap::remove(TKey k) {
    int value;
    // best case = T(1), worst case = T(numberOfElements), average case = T(numberOfElements), O(numberOfElements)
    for (int i = 0; i < numberOfElements; i++)
    {
        if (map[i].first == k)
        {
            value = map[i].second;
            for (int j = i + 1; j < numberOfElements; j++)
            {
                map[j - 1] = map[j];
            }
            numberOfElements--;
            return value;
        }
    }
    return NULL_TVALUE;
}

int SortedMap::size() const {
    if (isEmpty() == true)
        return 0;
    return numberOfElements;
}

TValue SortedMap::mostFrequent() const {
    if(isEmpty() == true)
        return NULL_TVALUE;

    int frequency[1000] = {0};
    int maxOfValues = 0;
    int maxFrequency = 0;
    int maxValue = 0;

    // best case = T(1), worst case = T(numberOfElements), average case = T(numberOfElements), O(numberOfElements)
    for(int i = 0; i < numberOfElements; i++)
    {
        if(maxOfValues < map[i].second)
            maxOfValues = map[i].second;
    }

    // best case = T(1), worst case = T(numberOfElements), average case = T(numberOfElements), O(numberOfElements)
    for(int i = 0; i < numberOfElements; i++)
    {
        frequency[map[i].second] += 1;
    }

    // best case = T(1), worst case = T(maxOfValues), average case = T(maxOfValues), O(maxOfValues)
    for(int i = 0; i <= maxOfValues; i++)
    {
        if(frequency[i] > maxFrequency)
        {
            maxFrequency = frequency[i];
            maxValue = i;
        }
    }
    return maxValue;
}

bool SortedMap::isEmpty() const {
    if (numberOfElements == 0)
        return true;
    return false;
}

SMIterator SortedMap::iterator() const {
    return SMIterator(*this);
}

SortedMap::~SortedMap() {
    delete[] map;
    numberOfElements = 0;
    capacity = 0;
}

