#ifndef HashTable_h
#define HashTable_h

#include <vector>

#define HASH_TABLE_STANDARD_CAPACITY 0

template <class tdata>
class HashTable
{
private:

	vector<tdata> data;

	// Length is the size of the Hash Table array.
	int length;

	// Returns an array location for a given item key.
	int hash(string itemKey);

public:

	HashTable(int tableLength = 0);

	// Adds an item to the Hash Table.
	void insertItem(tdata * newItem);

	// Deletes an Item by key from the Hash Table.
	// Returns true if the operation is successful.
	bool removeItem(string itemKey);

	// Returns an item from the Hash Table by key.
	// If the item isn't found, a null pointer is returned.
	tdata * getItemByKey(string itemKey);

	// Display the contents of the Hash Table to console window.
	void printTable();

	// Prints a histogram illustrating the Item distribution.
	void printHistogram();

	// Returns the number of locations in the Hash Table.
	int getLength();

	// Returns the number of Items in the Hash Table.
	int getNumberOfItems();

	// De-allocates all memory used for the Hash Table.
	~HashTable();
};

#endif






























