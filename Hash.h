#ifndef __HASH_H_INCLUDED__
#define __HASH_H_INCLUDED__
#include <string>
using namespace std;

class Hash {

private:

	static const long int tableSize = 200000;
	int numberOfItems;

	struct item {
		string word;
		int count;
	};

	item* hashTable[tableSize];








public:

	Hash();

	int hasher(string key);

	//int numberOfItemsInIndex(int index);

	void printTable();

	//void printItemsInIndex(int index);

	void search(string word);

	void deleteOne(string word);

	void insert(string word);
	void parseFileInsert(string fullPath);

	void lexSort();
	void split(string h[], int low, int high);
	void merge(string a[], int low, int high, int mid);

	void rangeSearch(string begin, string end);
};
#endif