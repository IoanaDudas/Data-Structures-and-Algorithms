#pragma once
#include<vector>
#include<utility>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TELEM pair<int,int>(-11111, -11111)
#define CAPACITY 32
#define NULL_TVALUE -11111
#define NULL_GOL int -111111

typedef bool (*Condition)(TValue);

class MultiMapIterator;

class MultiMap
{
	friend class MultiMapIterator;

private:
	//TODO - Representation
	int capacity;
	TElem* DynamicVector;
	int length;
    int maxFactor;

public:
	//constructor
	MultiMap();

	//adds a key value pair to the multimap
	void add(TKey c, TValue v);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	bool remove(TKey c, TValue v);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	vector<TValue> search(TKey c) const;

	//returns the number of pairs from the multimap
	int size() const;

	//checks whether the multimap is empty
	bool isEmpty() const;

	//returns an iterator for the multimap
	MultiMapIterator iterator() const;

    //keeps in the MultiMap only those pairs whose value respects the given condition
    void filter(Condition cond);


	//descturctor
	~MultiMap();

	int hash(TKey k, int i) const;

	int hashI(int i) const;

	void resize();

};

