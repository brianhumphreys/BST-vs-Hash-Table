
#ifndef __BST_H_INCLUDED__
#define __BST_H_INCLUDED__
#include <string>
using namespace std;

class BST 
{
    private:
        //structure of nodes
        struct node {
            std::string word;
            int count;
            struct node* leftChild;
            struct node* rightChild;
        };
        struct node *root;

        int nodeCount;
        

    public:
    
        //default constructor
        BST();
        //constructors with arguments
        BST(string word, int count);
        BST(string word);


        //deconstructor
        ~BST();
        void DestroyRecursive(node* node);

        void printNodeCount();

        //void printRoot();
        //Print function for developer uses
        void printInOrder();
        void pio(node* ptr);
        
        //A function for searching a word in the BST/Hash Table (the word may or may not exist).
        bool search(std::string word);
        bool search(node *ptr, string word);

        //A function for inserting a new word into the BST/Hash Table or increment the counter
        //if the word is already inserted.
        void insert(string word);
        void insert(string word, struct node *leaf);
        void parseFileInsert(string fullPath);

        //A function for deleting a word from the BST/Hash Table if the counter reaches zero or
        //decrement the counter by one. Deletion of already deleted word should be ignored.
        void deleteOne(std::string word);
        void deleteOne(node *ptr, string word);

        //A function to sort all the words lexicographically
        void lexSort();
        void lexSort(node *ptr, ofstream &outputFile);

        //A function for doing a range search. The function takes as input two words. Given two
        //words, the function should find all the words in between. The resulting words need not
        //be sorted.
        //this will return a pointer to an array of words
        vector<string> rangeSearch(string begin, string end);
        void rangeSearch(node *node, vector<string>& rangeVecotr, string low, string high);



};

#endif

