#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "BST.h"

using namespace std;

BST::BST(void) {
    root = NULL;
    nodeCount = 0;

    cout << "Default object is being creating." << "\n";
};
/*
BST::BST(string word, int count) {
    cout << "Default object is being creating." << "\n";
    this->root->word = word;
    this->root->count = count;
};

BST::BST(string word) {
    cout << "Default object is being creating." << "\n";
    this->root->word = word;
    this->root->count = 1;
};
*/

BST::~BST()
{
    DestroyRecursive(root);
}

void BST::DestroyRecursive(node* node)
{
    if (node)
    {
        DestroyRecursive(node->leftChild);
        DestroyRecursive(node->rightChild);
        delete node;
    }
}

//function to check the existence of a word in a BST
bool BST::search(string word) {
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    return search(root, word);
};

void BST::printNodeCount() {
    cout << nodeCount << endl;
}

//recursive helper frunction
bool BST::search(node *ptr, string word) {
    if (ptr == NULL) {
        //cout << "it does not exist:(" << endl; 
        cout << "false" << endl;
        return false;
    }
    else if (ptr->word > word) {
        //cout << "left" << endl;
        search(ptr->leftChild, word);
    }
    else if (ptr->word < word){
        //cout << "right" << endl;
        search(ptr->rightChild, word);
    }
    else {
        //cout << "it exists" << endl;
        cout << "true" << endl;
        return true;
    }
}

void BST::printInOrder() {
    pio(this->root);
}

void BST::pio(struct node* node) {
    if (node != NULL){
        
        /* first recur on left child */
        pio(node->leftChild);
        
        /* then print the data of node */
        cout << "Word: " << node->word << endl;
        cout << "Count: " << node->count << endl;  

        /* now recur on right child */
        pio(node->rightChild);
        
    }
    
};
void BST::insert(string word)
{ 
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    if(this->root != NULL){
        insert(word, this->root);
    }
    else
    {
        this->root = new node;
        this->root->word = word;
        this->root->count = 1;
        this->root->leftChild = NULL;
        this->root->rightChild = NULL;
    }
};

void BST::insert(string word, struct node *leaf)
{
    if(word < leaf->word)
    {
        
        if(leaf->leftChild != NULL)
            insert(word, leaf->leftChild);
        else
        {
            nodeCount += 1;

            leaf->leftChild = new node;
            leaf->leftChild->word = word;
            leaf->leftChild->count = 1;
            leaf->leftChild->leftChild = NULL;    //Sets the leftChild child of the child node to null
            leaf->leftChild->rightChild = NULL;   //Sets the rightChild child of the child node to null
        }  
    }
    else if(word > leaf->word)
    {
        
        if(leaf->rightChild != NULL)
            insert(word, leaf->rightChild);
        else
        {
            nodeCount += 1;
            
            leaf->rightChild = new node;
            leaf->rightChild->word = word;
            leaf->rightChild->count = 1;
            leaf->rightChild->leftChild = NULL;  //Sets the leftChild child of the child node to null
            leaf->rightChild->rightChild = NULL; //Sets the rightChild child of the child node to null
        }
    }
  //word is already in the tree so we increment counter
  else  leaf->count += 1;
};

void BST::parseFileInsert(string fullPath) {
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

void BST::deleteOne(string word) {
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    deleteOne(root, word);
    /*else {
        cout << "\"" <<  word << "\"" << " does not exist in the tree." << endl;
    }*/
};

void BST::deleteOne(node *ptr, string word) {
    // Find the word 
    bool found = false;
    node* predecessor=nullptr;
    node* current=ptr;
    if(current==nullptr) {
        //do nothing
        //cout<<"Tree is empty"<<endl;
        return;
     }
    while(current!=nullptr)
    {
        if(current->word==word)
        {
            found = true;
            break;
        }
        else
        {
            predecessor = current;
            if(word > (current->word))
                current=current->rightChild;
            else
                current=current->leftChild;
        }
    }
    if(!found)
    {
        //do nothing
        //cout<<word<<" not in Tree."<<endl;
        return;
    }

    //If the count of the word is greater than 1, we only need to decrement the counter
    if ( current->count > 1 ) {
        current->count -= 1;
    }
    //if there is only one instance of the word in the tree, we must delete the node
    else {

        // CASE 1: Removing a node with a single child
        if((current->leftChild==nullptr && current->rightChild != nullptr) || (current->leftChild != nullptr && current->rightChild==nullptr))
        {
            // RightChild Leaf Present, No LeftChild Leaf
            if(current->leftChild==nullptr && current->rightChild != nullptr)
            {
                // If predecessor's leftChild tree equals node ptr
                if(predecessor->leftChild==current)
                {
                    // then predecessor's leftChild tree becomes ptr's rightChild tree
                    // and delete ptr
                    predecessor->leftChild=current->rightChild;
                    delete current;
                    current=nullptr;
                    //cout<<word<<" has been removed from the Tree."<<endl;
                }
                // If predecessor's rightChild tree equals node ptr
                else
                {
                    // then predecessor's rightChild tree becomes ptr's rightChild tree
                    // and delete ptr
                    predecessor->rightChild=current->rightChild;
                    delete current;
                    current=nullptr;
                    //cout<<word<<" has been removed from the Tree."<<endl;
                }
            }
            else // LeftChild Leaf Present, No RightChild Leaf Present
            {
                if(predecessor->leftChild==current)
                {
                    predecessor->leftChild=current->leftChild;
                    delete current;
                    current=nullptr;
                    //cout<<word<<" has been removed from the Tree."<<endl;
                }
                else
                {
                    predecessor->rightChild=current->leftChild;
                    delete current;
                    current=nullptr;
                    //cout<<word<<" has been removed from the Tree."<<endl;
                }
            }
            return;
        }
        // CASE 2: Removing a Leaf node
        if(current->leftChild==nullptr && current->rightChild==nullptr)
        {
            if(predecessor->leftChild==current)
                predecessor->leftChild=nullptr;
            else
                predecessor->rightChild=nullptr;
            delete current;
            //cout<<word<<" has been removed from the Tree."<<endl;
            return;
        }
        // CASE 3: node has two children
        // Replace node with smallest value in rightChild subtree
        if(current->leftChild != nullptr && current->rightChild != nullptr)
        {
            node* check=current->rightChild;
            if((current->leftChild==nullptr)&&(current->rightChild==nullptr))
            {
                current=check;
                delete check;
                //current->rightChild==nullptr;
                //cout<<word<<" has been removed from the Tree."<<endl;
            }
            else // RightChild child has children
            {
                // If the node's rightChild child has a leftChild child
                // Move all the way down leftChild to locate smallest element
                if((current->rightChild)->leftChild!=nullptr)
                {
                    node* leftCurrent;
                    node* leftCurrentPred;
                    leftCurrentPred=current->rightChild;
                    leftCurrent=(current->rightChild)->leftChild;
                    while(leftCurrent->leftChild != nullptr)
                    {
                        leftCurrentPred=leftCurrent;
                        leftCurrent=leftCurrent->leftChild;
                    }
                    current->word=leftCurrent->word;
                    delete leftCurrent;
                    //leftCurrentPred->leftChild==nullptr;
                    //cout<<word<<" has been removed from the Tree."<<endl;
                }
                else
                {
                    node* temp=current->rightChild;
                    current->word=temp->word;
                    current->rightChild=temp->rightChild;
                    delete temp;
                    //cout<<word<<" has been removed from the Tree."<<endl;
                }
            }
            return;
        }
    }
    
};

void BST::lexSort() {
    ofstream outputFile;
    outputFile.open("bstSorted.txt");
    lexSort(this->root, outputFile);
    outputFile.close();
};

void BST::lexSort(node *node, ofstream &outputFile) {
    if (node != nullptr){
        
        /* first recur on left child */
        lexSort(node->leftChild, outputFile);
        
        /* then write the data of node to an output file */
        outputFile << node->word << " ";
        //cout << node->word << "being written." << endl;
        /* now recur on right child */
        lexSort(node->rightChild, outputFile);
        
    }
}

vector<string> BST::rangeSearch(string begin, string end) {
    /*bool foundBegin = false;
    bool foundEnd = false;*/
    if (begin > end) {
        string temp = begin;
        begin = end;
        end = temp;
    }
    vector<string> rangeVector;
    rangeSearch(root, rangeVector, begin, end);
    return rangeVector;
};

// Returns count of nodes in BST in range [low, high]
void BST::rangeSearch(node *node, vector<string>& rangeVector, string low, string high) {
    // Base case
    if (node == NULL) return;
 
    // Special Optional case for improving efficiency
    //if (node->word == high && node->word == low)
        //cout << "adding to vector." << endl;
        //rangeVector.push_back(node->word);
 
    // If current node is in range, then include it in count and
    // recur for left and rightChild children of it
    if (node->word <= high && node->word >= low){
        
        //cout << node->word << endl;
        //cout << "adding to vector." << endl;
        rangeSearch(node->leftChild, rangeVector, low, high);
        rangeVector.push_back(node->word);
        cout << node->word << endl;
        rangeSearch(node->rightChild, rangeVector, low, high);
    }
    // If current node is smaller than low, then recur for rightChild
    // child
    else if (node->word < low) {
         rangeSearch(node->rightChild, rangeVector, low, high);
    }
    // Else recur for leftChild child
    else rangeSearch(node->leftChild, rangeVector, low, high);
}





















