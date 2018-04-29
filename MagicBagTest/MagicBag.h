/*
*******************************************************************************************************
Task:	Project 1																			Points
You can create a magic bag of integers and insert integers into the bag.	(done)			5
You can create a magic bag of any primitive data type and insert items into the bag.		5
The capacity of the magic bag is limited only by the amount of available RAM.				5
The peek() member function returns a value without deleting any items from the bag.			5
The draw() member function returns and removes an item from the bag.						5
The probability of drawing an item from the bag is equall for all items.					5
You can print Magic Bags to cout using the print(ostream&) member function.					5
Magic bags can be copied and assigned, resulting in a new,
independent bag with the same contents as the original bag.									5
You code has no memory leaks.																5
Your Project is well written, well documented, and well structured.							5										*

*******************************************************************************************************/
#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib> //for random number generation

using namespace std;

template <class T>

struct Node
{
	struct Node<T> * next;
	T data;
};

template<class T> class MagicBag
{
public:

	MagicBag()
	{
		head = NULL;
		count = 0;
	}

	MagicBag(const MagicBag& other)
	{

		head = NULL;
		count = 0;
		*this = other;

	}
	MagicBag& operator=(const MagicBag& other)
	{
		deleteAll();
		Node<T> *current = other.head;
		while (current != NULL)
		{
			insert(current->data);
			current = current->next;
		}
		return *this;
	}
	/*
	* destructor
	* takes care of memory leaks
	*/
	~MagicBag()
	{
		deleteAll();
	}

	void insert(T item)
	{

		Node<T> * n = new Node<T>();
		n->data = item;
		n->next = head;
		head = n;
		count++;
	}
	/*
	Objects are removed from the magic bag using the MagicBag::draw() member function.
	This function returns a random item and removes it from the bag.
	The returned item should be randomized.
	In other words, if there are 5 items in the bag, and only one of them is a 7,
	then there should be a 1 in 5 chance of drawing a 7 with the draw() function.
	If the bag is empty, the draw() function should throw an exception.
	*/
	T draw()
	{
		if (empty()) // should never get to see this message.. bag should never be empty if it follows the test function.
		{
			throw "Magic Bag is empty";
			//return 0;
		}

		int index = rand() % count; //generates a random number 
		Node<T> * previous = NULL;
		Node<T> * current = head;

		for (int i = 0; i < index; i++)
		{
			previous = current;
			current = current->next;
		}
		T val = current->data;
		if (current == head)
		{
			head = head->next;
		}
		else
		{
			previous->next = current->next;
		}
		delete current;
		count--;
		return val;
	}
	/*
	*You can check if an object is in the bag using MagicBag::peek(item),
	*which should return 0 if there is no item in the bag matching the item parameter.
	*If there are items matching the item parameter in the bag,
	*the number (count) of matching items should be returned.
	*counts the number of 111's in the main program 'magicbag.cpp'
	*/
	int peek(T item)
	{
		if (empty())
		{
			return 0;
		}
		else
		{
			Node<T> * current = head;
			int total = 0;
			while (current != NULL)
			{
				if (current->data == item)
				{
					total++;
				}
				current = current->next;
			}
			return total;
		}
	}

	void print(ostream & os)
	{
		os << *this;
	}
	/*
	* size method
	* returns the count of items in bag (number of 111's in bag)
	*/
	int size()
	{
		return count;
	}
	/*
	*
	* if bag is empty return 0
	*
	*/
	bool empty()
	{
		return count == 0;
	}

private:
	Node<T> * head;
	int count;


	friend ostream & operator << (ostream & os, const MagicBag & mb)
	{
		Node<T> * current = mb.head;
		while (current != NULL)
		{
			os << current->data << " ";
			current = current->next;
		}
		os << endl;
		return os;
	}

	//a helper function to delete the list contents  
	//used by destructor and assignment operator
	void deleteAll()
	{
		Node<T>* current = head;
		Node<T>* temp;

		while (current != NULL)
		{
			temp = current->next;
			delete current;
			current = temp;
		}
		head = NULL;
		count = 0;
	}
};