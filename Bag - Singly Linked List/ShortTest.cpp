#include "ShortTest.h"
#include <assert.h>
#include "Bag.h"
#include "BagIterator.h"
#include <exception>


void testAll() { 
	Bag b;
	assert(b.isEmpty() == true);
	assert(b.size() == 0); 
	b.add(5);
	b.add(1);
	b.add(10);
	b.add(7);
	b.add(1);
	b.add(11);
	b.add(-3);
	assert(b.size() == 7);
	assert(b.search(10) == true);
	assert(b.search(16) == false);
	assert(b.nrOccurrences(1) == 2);
	assert(b.nrOccurrences(7) == 1);
	assert(b.remove(1) == true);
	assert(b.remove(6) == false);
	assert(b.size() == 6);
	assert(b.nrOccurrences(1) == 1);
	BagIterator it = b.iterator();
	it.first();
	while (it.valid()) {
		TElem e = it.getCurrent();
		it.next();
	}

	b.addOccurrences(4, 20);
	assert(b.size() == 10);
	assert(b.search(20) == true);
	assert(b.nrOccurrences(20) == 4);

	assert(b.nrOccurrences(7) == 1);
	b.addOccurrences(5, 7);
	assert(b.size() == 15);
	assert(b.nrOccurrences(7) == 6);

	try{
	    b.addOccurrences(-7, 8);
	    assert(false);
	}
    catch (std::exception&) {
        assert(true);
    }
}
