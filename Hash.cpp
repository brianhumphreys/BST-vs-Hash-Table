#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <math.h>

#include "Hash.h"

using namespace std;

Hash::Hash() {
	for(int i = 0; i < tableSize; i++) {
		hashTable[i] = new item;
		hashTable[i]->word = "";
		hashTable[i]->count = 0;
	}
	numberOfItems = 0;
}



int Hash::hasher(string key) 
{
	//transform(key.begin(), key.end(), key.begin(), ::tolower);
	int hash = 0;
	int index;

	for(int i = 0; i < key.length(); i++) {
		hash += (int)key[i] * pow(i,3) * 3;
		//cout << "hash = " << hash << endl;
	}

	index = hash % tableSize;
	return index;
}


void Hash::insert(string word) {
	//get hash value of the new word
	transform(word.begin(), word.end(), word.begin(), ::tolower);
	int index = hasher(word);

	//if the bucket is empty, override the empty bucket values
	if(hashTable[index]->word == "") {
		hashTable[index]->word = word;
		hashTable[index]->count = 1;
		numberOfItems += 1;
	}

	else if(hashTable[index]->word == word) {
		hashTable[index]->count += 1;
	}
	
	//iterate down the table to find the first vacant spot or
	//the same word that is being inserted
	else {
		int i = 1;
		while((hashTable[((index + i) % tableSize)]->word != "") && (hashTable[(index + i) % tableSize]->word != word)) {
			i +=1;
		}

		//set the index to the first vacant spot after a collision occurred
		index = (index + i) % tableSize;
		//in this case, the iteration found a vacant spot
		if(hashTable[index]->word == "") {
			hashTable[index]->word = word;
			hashTable[index]->count = 1;
			numberOfItems += 1;
		} 
		//in this case, the iteration found the same word
		else {
			hashTable[index]->count += 1;
		}
	}
}

void Hash::printTable() {
	int number;
	for(int i = 0; i < tableSize; i++) {
		

		cout << "----------------------------------" << endl;
		cout << "index = " << i << endl;
		cout << "word = " << hashTable[i]->word << endl;
		cout << "counter = " << hashTable[i]->count << endl;
	}
}

void Hash::search(string word) 
{
	transform(word.begin(), word.end(), word.begin(), ::tolower);
	int index = hasher(word);
	bool foundName = false;

	//iterate until your reach end of list or
	//until the word is found
	for(int i = 0; i < tableSize; i++) {
		if(hashTable[(index + i) % tableSize]->word == word) {
			foundName = true;
			index += i;
			break; }
	}

	if(foundName) cout << "true" << endl; 
	else cout << "false" << endl;
}
	

void Hash::deleteOne(string word) {

	transform(word.begin(), word.end(), word.begin(), ::tolower);
	int index = hasher(word);
	cout << hashTable[index]->word << endl;

	//Case 0 - bucket is empty
	if(hashTable[index]->word == "") {
		//do nothing
		//cout << word << " was not found in the table." << endl;
		return;
	}

	//Case 2 - match is located in the first item in the 
	//bucket but there are more items in the nucket
	else if(hashTable[index]->word == word) {

		if(hashTable[index]->count == 1) {
			hashTable[index]->word = "";
			hashTable[index]->count = 0;
			numberOfItems -= 1;

			//cout << word << " was removed from the Hash table." << endl;
		}
		else {
			hashTable[index]->count -= 1;

			//cout << "One item from the count was removed." << endl;
		}
		
	}

	//Case 3 - bucket contains items but first item is
	//not a match
	else {
		bool foundName = false;

		for(int i = 0; i < tableSize; i++) {
			if(hashTable[(index + i) % tableSize]->word == word) {
				foundName = true;
				break; }
		} 
		if (!foundName) {
			//cout << word << " was not found in the table." << endl;
			return;
		}
		else {
			if(hashTable[index]->count == 1) {
				hashTable[index]->word = "";
				hashTable[index]->count = 0;
				numberOfItems -= 1;

				//cout << word << " was removed from the Hash table." << endl;
			}
			else {
				hashTable[index]->count -= 1;

				//cout << "One item from the count was removed." << endl;
			}
			
		}
		
	}
	//cout << "Number of words in index: " << hashTable[index]->count << endl;

	
}

void Hash::parseFileInsert(string fullPath) {
    ifstream infile(fullPath); // Open it up!
    std::string line;
    char c;
    string word = "";
    //int jerry = 0;
    while (std::getline(infile, line))
    {
        // Iterate through the string one letter at a time.
        for (int i = 0; i < line.length(); i++) {

            c = line.at(i); // Get a char from string
            tolower(c);        
            // if it's NOT within these bounds, then it's not a character
            if (! ( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) ) ) {

                //if word is NOT an empty string, insert word into bst
                if ( word != "" ) {
                    insert(word);
                    //jerry += 1;
                    //cout << jerry << endl;
                    //reset word string
                    word = "";
                }
            }
            else {
                word += string(1, c);
            }
         }
     }
     
};

void Hash::lexSort() {
	string wordArray[numberOfItems];
	int index = 0;

	for(int i = 0; i < tableSize; i++) {
		if (hashTable[i]->count != 0) {
			wordArray[index] = hashTable[i]->word;
			index += 1;
		}
	}
	
	split(wordArray, 0, numberOfItems - 1);

	ofstream outputFile;
	outputFile.open("hashSorted.txt");
	
	for(int i = 0; i < numberOfItems; i++) {
		outputFile << wordArray[i] << " ";
	}
	

}

void Hash::split(string h[], int low, int high)
{
	int mid;
	if (low < high)
	{
		mid=(low+high)/2;
		// Split the data into two half.
		split(h, low, mid);
		split(h, mid+1, high);
 
		// Merge them to get sorted output.
		merge(h, low, high, mid);
	}
}

// A function to merge the two half into a sorted data.
void Hash::merge(string a[], int low, int high, int mid)
{
	// We have low to mid and mid+1 to high already sorted.
	int i, j, k;
	string temp[high-low+1];
	i = low;
	k = 0;
	j = mid + 1;
 
	// Merge the two parts into temp[].
	while (i <= mid && j <= high)
	{
		if (a[i] < a[j])
		{
			temp[k] = a[i];
			k++;
			i++;
		}
		else
		{
			temp[k] = a[j];
			k++;
			j++;
		}
	}
 
	// Insert all the remaining values from i to mid into temp[].
	while (i <= mid)
	{
		temp[k] = a[i];
		k++;
		i++;
	}
 
	// Insert all the remaining values from j to high into temp[].
	while (j <= high)
	{
		temp[k] = a[j];
		k++;
		j++;
	}
 
 
	// Assign sorted data stored in temp[] to a[].
	for (i = low; i <= high; i++)
	{
		a[i] = temp[i-low];
	}
}

void Hash::rangeSearch(string begin, string end) {
	string wordArray[numberOfItems];
	int index = 0;

	//create array to be sorted
	for(int i = 0; i < tableSize; i++) {
		if (hashTable[i]->count != 0) {
			wordArray[index] = hashTable[i]->word;
			index += 1;
		}
	}
	
	//sort array
	split(wordArray, 0, numberOfItems - 1);

	//find the index of the first word
	int startIndex = 0; 
	while(wordArray[startIndex] < begin) {
		startIndex += 1;
	}

	
	/*
	cout << "range 10: " << wordArray[startIndex + 10] << endl;
	cout << "range 100: " << wordArray[startIndex + 100] << endl;
	cout << "range 1000: " << wordArray[startIndex + 1000] << endl;*/
	cout << hashTable[index]->word << endl;

	//find the index of the last word
	int endIndex = startIndex;
	while(wordArray[endIndex] <= end) {
		endIndex += 1;
	}

	for(int i = startIndex; i < endIndex; i++) {
		cout << wordArray[i] << endl;
	}

}




















