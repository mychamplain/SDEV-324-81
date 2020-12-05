/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Champlain College SDEV-345-81
 *
 * C++ Week 13: Hash Tables - (2020/12/06)
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Write a menu driven program that creates a hash table using an array.
 * The program should give the user the following options and should run in an infinite loop:
 *    1) Insert key
 *    2) Delete key
 *    3) Display hash table
 *    4) Find key
 * The key should be a string and the program should calculate the location using a hash function.
 * The program should also prompt the user when there is a collision and when the hash table is full.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Written by Llewellyn van der Merwe <llewellyn.vandermerw@mymail.champlain.edu>, December 2020
 * Copyright (C) 2020. All Rights Reserved
 * License GNU/GPL Version 2 or later - http://www.gnu.org/licenses/gpl-2.0.html
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// Based on the examples from Paul Programming series on Hash tables
// https://www.youtube.com/playlist?list=PLTxllHdfUq4f7-uHOpxXnBUbsuLiI9pmb

#include <iostream>
#include <string>
#include <limits>

using namespace std;

class HashTable{
private:
    // never use this as a value ;)
    const string emptyString = "|//_-++-_0.^.0_-++-_\\|";
    // the size of the array
    static const int tableSize = 5;
    // the node to store in hash table array
    struct node{
        string value;
        node* next;
    };
    // the HashBucket table array of nodes
    node* HashBucket[tableSize];
    // search for value in table
    bool find(string &value){
        // get the HashBucket value of the string
        int key = Hash(value);
        // continue the search
        return find(key, value);
    }
    // smart search by key and value
    bool find(int &key, string &value){
        // check if the HashBucket has a collision
        if (HashBucket[key]->value == value){
            // found
            return true;
        } else if (HashBucket[key]->next != nullptr) {
            // continue the search
            return find(HashBucket[key]->next, value);
        }
        return false;
    }
    // smart search in node with value
    bool find(node* bucket, string &value){
        // check if the value is found
        if (bucket->value == value){
            // found
            return true;
        } else if (bucket->next != nullptr) {
            // continue the search
            return find(bucket->next, value);
        }
        // value is not found
        return false;
    }
    // display each bucket
    void display(node* bucket){
        // print out the value
        cout << bucket->value;
        // loop over all the buckets
        if (bucket->next != nullptr) {
            cout << "; "; // little spacer :)
            display(bucket->next);
        }
    }

public:
    // our constructor of our HashBucket table
    HashTable(){
        // initialize the empty HashBucket tables
        for(int i = 0; i < tableSize; i++) {
            HashBucket[i] = new node;
            HashBucket[i]->value = emptyString;
            HashBucket[i]->next = nullptr;
        }
    };
    // our destructor of our HashBucket table
    ~HashTable(){

    }
    // our HashBucket function
    int Hash(string key) {
        int hash = 0;
        int tmp = key.length();
        // now loop the string value-key to get HashBucket
        for (int i = 0; i < tmp; i++) {
            hash = hash + (int) key[i];
        }
        // return the remainder
        return hash % tableSize;
    }
    // add a node value
    void insert(string value)
    {
        // get the HashBucket value of the string
        int key = Hash(value);
        // check if the HashBucket has a collision
        if (HashBucket[key]->value == emptyString){
            // give success adding info
            cout << "█ [Info] " << value << " - added successfully." << endl;
            // new value
            HashBucket[key]->value = value;
        } else {
            // get the first item
            node *firstNode = HashBucket[key];
            // check if the values are the same
            if(!find(firstNode, value)) {
                // prom the user if we should add to bucket
                cout << "█ [Warning] Collision detected." << endl;
                cout << "█ Do you still want to add: " << value << endl;
                cout << "█ Enter initial [yes/no]: ";
                char choice;
                cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    // give collision warning
                    cout << "██████████████████████████████████████████████████████████" << endl;
                    cout << "█ Collision resolved!" << endl;
                    cout << "█ [Info] " << value << " - added amicably." << endl;
                    // create a new node
                    node *newNode = new node;
                    newNode->value = value;
                    newNode->next = firstNode;
                    // add the new node
                    HashBucket[key] = newNode;
                } else {
                    // give notice
                    cout << "█ [Notice] " << value << " - not added." << endl;
                }
            } else {
                // give collision error
                cout << "█ [Error] " << value << " - exists." << endl;
            }
        }
        cout << "██████████████████████████████████████████████████████████" << endl;
        return;
    }
    // search if the value is in the hash table
    void search(string &value){
        // use the find method/function
        if (find(value)){
            cout << "█ [Success] " << value << " - found" << endl;
        } else {
            cout << "█ [Notice] " << value << " - not found" << endl;
        }
        cout << "██████████████████████████████████████████████████████████" << endl;
        return;
    }
    // display the hash table
    void display(){
        cout << "███ THE HASH TABLE BUCKETS  ██████████████████████████████" << endl;
        cout << "██████████████████████████████████████████████████████████" << endl;
        // loop over all the buckets
        int tableFull = 0;
        for(int i = 0; i < tableSize; i++) {
            // only print out if bucket has values
            if (HashBucket[i]->value != emptyString) {
                cout << "█ Bucket Nr: " << i << " {";
                display(HashBucket[i]);
                cout << "}" << endl;
                cout << "██████████████████████████████████████████████████████████" << endl;
                tableFull++;
            } else {
                // empty notice
                cout << "█ Bucket Nr: " << i << " is empty" << endl;
                cout << "██████████████████████████████████████████████████████████" << endl;
            }
        }
        if (tableSize == tableFull){
            cout << "███ EACH TABLE BUCKET HAS A VALUE ████████████████████████" << endl;
        } else {
            cout << "███ TABLE BUCKETS NOT FULL ███████████████████████████████" << endl;
        }
        return;
    }
    // delete a value from the table
    void remove(string value){
        // get the HashBucket value of the string
        int key = Hash(value);
        // the table does not have this value
        if (HashBucket[key]->value == emptyString) {
            // not found notice
            cout << "█ [Notice] " << value << " - not found." << endl;
        }
        // last value added to bucket is a match
        else if (HashBucket[key]->value == value && HashBucket[key]->next == nullptr){
            // remove the value
            HashBucket[key]->value = emptyString;
            // removed notice
            cout << "█ [Success] " << value << " - removed." << endl;
        }
        // last value added to bucket is a match but there is more nodes
        else if (HashBucket[key]->value == value){
            // get the last node
            node* delPtr = HashBucket[key];
            // move the next node up
            HashBucket[key] = delPtr->next;
            // remove the last added value
            delete delPtr;
            // removed notice
            cout << "█ [Success] " << value << " - removed." << endl;
        } else {
            // some tmp pointers
            node* P1 = HashBucket[key];
            node* P2 = HashBucket[key]->next;
            // lets start the search
            while (P1 != nullptr && P1->value != value) {
                // no match found, and not at end yet
                P2 = P1;
                P1 = P1->next;
            }
            // if no match was found
            if (P1 == nullptr) {
                // not found notice
                cout << "█ [Notice] " << value << " - not found." << endl;
            }
            // so seems like value is found
            else {
                // set the node to delete
                node* delPtr = P1;
                // do the swap
                P1 = P1->next;
                P2->next = P1;
                // remove the last added value
                delete delPtr;
                // removed notice
                cout << "█ [Success] " << value << " - removed." << endl;
            }
        }
        cout << "██████████████████████████████████████████████████████████" << endl;
        return;
    }
};

int main (){
    // instantiate the table
    HashTable Table;
    // program loop (taken and adapted from this weeks module)
    char choice = 'b';
    string aKey;
    // start the program
    cout << "██████████████████████████████████████████████████████████" << endl;
    // interact with user
    while(choice != 'x')
    {
        cout << "█ Enter first letter of "
             << "show, insert, delete, or find: ";
        char choice;
        cin >> choice;
        // clear cin stream
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch(choice)
        {
            case 's':
                Table.display();
                break;
            case 'i':
                cout << "█ Enter key value to insert: ";
                getline( cin, aKey );
                // now insert the string
                Table.insert(aKey);
                break;
            case 'd':
                cout << "█ Enter key value to delete: ";
                getline( cin, aKey );
                // now remove the string
                Table.remove(aKey);
                break;
            case 'f':
                cout << "█ Enter key value to find: ";
                getline( cin, aKey );
                // now search for the string
                Table.search(aKey);
                break;
            default:
                cout << "█ Invalid entry\n";
                break;
        }
    }
}