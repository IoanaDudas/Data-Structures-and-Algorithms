#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

// best case = Theta(1), worst case = Theta(1), average case = Theta(1), O(1)
Bag::Bag() {

    this->bagSll = new sll();
    this->bagSll->head = NULL;
}

// best case = Theta(1), worst case = Theta(numberOfElements), average case = Theta(numberOfElements), O(numberOfElements)
void Bag::add(TElem elem) {
    if(isEmpty())
    {
        sllNode *newNode = new sllNode();
        newNode->data = elem;
        newNode->frequency = 1;
        newNode->next = NULL;
        this->bagSll->head = newNode;
    }
    else
    {
        sllNode *current = this->bagSll->head;
        while(current->next != NULL)
        {
            if(current->data == elem)
            {
                current->frequency++;
                return;
            }
            current = current->next;
        }
        if(current->data == elem)
        {
            current->frequency++;
            return;
        }
        sllNode *newNode = new sllNode();
        newNode->data = elem;
        newNode->frequency = 1;
        newNode->next = NULL;
        current->next = newNode;
    }
}

// best case = Theta(1), worst case = Theta(numberOfElements), average case = Theta(numberOfElements), O(numberOfElements)
bool Bag::remove(TElem elem) {
    if(isEmpty())
        return false;
    else
    {
        sllNode *current = this->bagSll->head;
        sllNode *previous = this->bagSll->head;
        while(current != NULL and current->data != elem)
        {
            previous = current;
            current = current->next;
        }
        if(current == NULL)
            return false;
        else if(current->frequency > 1)
        {
            current->frequency--;
            return true;
        }
        else if(current == previous)// == NULL)
        {
            this->bagSll->head = this->bagSll->head->next;
            delete current;
            return true;
        }
        else if(current != NULL)
        {
            previous->next = current->next;
            current->next = NULL;
            delete current;
            return true;
        }
    }
}

// best case = Theta(1), worst case = Theta(numberOfElements), average case = Theta(numberOfElements), O(numberOfElements)
bool Bag::search(TElem elem) const {
    sllNode *current = this->bagSll->head;
    while(current != NULL)
    {
        if(current->data == elem)
            return true;
        current = current->next;
    }
	return false; 
}

// best case = Theta(1), worst case = Theta(numberOfElements), average case = Theta(numberOfElements), O(numberOfElements)
int Bag::nrOccurrences(TElem elem) const {
    sllNode *current = this->bagSll->head;
    while(current != NULL)
    {
        if(current->data == elem)
            return current->frequency;
        current = current->next;
    }
	return 0; 
}

// best case = Theta(numberOfElements), worst case = Theta(numberOfElements), average case = Theta(numberOfElements), O(numberOfElements)
int Bag::size() const {
    int size = 0;
    sllNode *current = this->bagSll->head;
    while(current != NULL)
    {
        size += current->frequency;
        current = current->next;
    }
    return size;
	//return 0;
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1), O(1)
bool Bag::isEmpty() const {
    if(this->bagSll->head == NULL)
        return true;
	return false;
}

// best case = Theta(1), worst case = Theta(1), average case = Theta(1), O(1)
BagIterator Bag::iterator() const {
  	return BagIterator(*this);
}

// best case = Theta(numberOfElements), worst case = Theta(numberOfElements), average case = Theta(numberOfElements), O(numberOfElements)
Bag::~Bag() {
    sllNode *current = this->bagSll->head;
    sllNode *currentNoDelete = this->bagSll->head;
    while(currentNoDelete != NULL)
    {
        currentNoDelete = currentNoDelete->next;
        delete current;
        current = currentNoDelete;
    }
    delete currentNoDelete;
    delete this->bagSll;
}

// best case = Theta(1), worst case = Theta(numberOfElements), average case = Theta(numberOfElements), O(numberOfElements)
void Bag::addOccurrences(int nr, TElem elem) {
    if(nr < 0)
        throw exception();
    else
    {
        if(isEmpty())
        {
            sllNode *newNode = new sllNode();
            newNode->data = elem;
            newNode->frequency = nr;
            newNode->next = NULL;
            this->bagSll->head = newNode;
        }
        else
        {
            sllNode *current = this->bagSll->head;
            while(current->next != NULL)
            {
                if(current->data == elem)
                {
                    current->frequency += nr;
                    return;
                }
                current = current->next;
            }
            if(current->data == elem)
            {
                current->frequency += nr;
                return;
            }
            sllNode *newNode = new sllNode();
            newNode->data = elem;
            newNode->frequency = nr;
            newNode->next = NULL;
            current->next = newNode;
        }
    }
}

