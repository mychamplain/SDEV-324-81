/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Champlain College SDEV-345-81
 *
 * C++ Week 14 Quadratic Probing, Hash Tables - (2020/12/13)
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Modify last week's program to demonstrate quadratic hash probing when a collision occurs.
 *
 * LAST WEEK
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

#include <iostream>
#include <string>
#include <limits>

using namespace std;

class HashTable {
private:
    // never use this as a value ;)
    const string emptyString = "|//_-++-_0.^.0_-++-_\\|";
    // the size of the array
    static const int tableSize = 8;
    // the inserted number
    int inserted = 0;
    // the HashBucket table array of nodes
    string HashBucket[tableSize];
    // found & empty key
    static const int emptyFoundKey = tableSize + 10;
    // found ;)
    int foundKey = emptyFoundKey;
    // empty ;)
    int emptyKey = emptyFoundKey;

    // search for value in table
    bool find(string &value) {
        // get the HashBucket value of the string
        int key = Hash(value);
        // check if the value is found
        if (HashBucket[key] == value) {
            // if found set key
            foundKey = key;
            // found
            return true;
        }
        // continue the search
        return find(key, value);
    }

    // smart search by key and value
    bool find(int &key, string &value) {
        // always reset the found
        emptyKey = emptyFoundKey;
        foundKey = emptyFoundKey;
        // use quadratic probing
        for (int pos = 0; pos < tableSize; pos++) {
            // Computing the new hash value
            key = Quadratic(key, pos);
            // check if the value is found
            if (HashBucket[key] == value) {
                // if found set key
                foundKey = key;
                // we found the value
                return true;
            } else if (HashBucket[key] == emptyString && emptyKey == emptyFoundKey) {
                // if first not found set key
                emptyKey = key;
                // but lets continue the search since on removal
                // we do not move the values to spaces
                // up to fill the array from the first hash
            }
        }
        return false;
    }

    // Hash function
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

    // quadratic insert function
    bool insert(int &key, string &value) {
        // check if key was found
        if (key != emptyFoundKey && HashBucket[key] == emptyString) {
            // since we have the key
            // we need to do the search
            // again
            HashBucket[key] = value;
            // count values inserted
            inserted++;
            // always reset just incase
            emptyKey = emptyFoundKey;
            return true;
        }
        // get the HashBucket value of the string
        key = Hash(value);
        // use quadratic probing
        for (int pos = 0; pos < tableSize; pos++) {
            // Computing the new hash value
            key = Quadratic(key, pos);
            if (HashBucket[key] == emptyString) {
                // Break the loop after
                // inserting the value
                // in the table
                HashBucket[key] = value;
                // count values inserted
                inserted++;
                return true;
            }
        }
        return false;
    }

    // quadratic function
    int Quadratic(int key, int pos) {
        // Computing the new hash value
        int hash = key + pos * pos;
        // return the remainder
        return hash % tableSize;
    }

public:
    // our constructor of our HashBucket table
    HashTable() {
        // initialize the empty HashBucket tables
        for (int i = 0; i < tableSize; i++) {
            HashBucket[i] = emptyString;
        }
    }

    // check if table is full
    bool isFull() {
        return inserted == tableSize;
    }

    // add a node value
    void insert(string value) {
        // get the HashBucket value of the string
        int key = Hash(value);
        // check if the HashBucket has a collision
        if (HashBucket[key] == emptyString) {
            // give success adding info
            cout << "█ [Info] " << value << " - added successfully." << endl;
            // new value
            HashBucket[key] = value;
            // count values inserted
            inserted++;
        }
            // check if the value exist
        else if (!find(value)) {
            // prom the user if we should add to table
            cout << "█ [Warning] Collision detected." << endl;
            cout << "█ Do you still want to add: " << value << endl;
            cout << "█ Enter initial [yes/no]: ";
            char choice;
            cin >> choice;
            if ((choice == 'y' || choice == 'Y') && insert(emptyKey, value)) {
                // give collision info
                cout << "██████████████████████████████████████████████████████████" << endl;
                cout << "█ Collision resolved!" << endl;
                cout << "█ [Info] " << value << " - quadratic probing used." << endl;
            } else if (choice == 'y' || choice == 'Y') {
                // give error of quadratic probing failure
                cout << "██████████████████████████████████████████████████████████" << endl;
                cout << "█ [Error] " << value << " - not added." << endl;
                cout << "█ [Error] " << " - Quadratic probing failed." << endl;
                cout << "█ [Error] " << " - The array needs to be enlarged." << endl;
            } else {
                // give notice
                cout << "█ [Notice] " << value << " - not added." << endl;
            }
        } else {
            // give exists error
            cout << "█ [Error] " << value << " - exists." << endl;
        }
        cout << "██████████████████████████████████████████████████████████" << endl;
        return;
    }

    // search if the value is in the hash table
    void search(string &value) {
        // use the find method/function
        if (find(value)) {
            cout << "█ [Success] (" << foundKey << ") => " << value << " - found" << endl;
        } else {
            cout << "█ [Notice] " << value << " - not found" << endl;
        }
        cout << "██████████████████████████████████████████████████████████" << endl;
        return;
    }

    // display the hash table
    void display() {
        cout << "███ THE HASH TABLE ███████████████████████████████████████" << endl;
        cout << "██████████████████████████████████████████████████████████" << endl;
        for (int i = 0; i < tableSize; i++) {
            // only print out if bucket has values
            if (HashBucket[i] != emptyString) {
                cout << "█ (" << i << ") => ";
                cout << HashBucket[i] << endl;
                cout << "██████████████████████████████████████████████████████████" << endl;
            } else {
                // empty notice
                cout << "█ (" << i << ") =-" << endl;
                cout << "██████████████████████████████████████████████████████████" << endl;
            }
        }
        if (isFull()) {
            cout << "███ TABLE IS FULL ████████████████████████████████████████" << endl;
        } else {
            cout << "███ TABLE NOT FULL ███████████████████████████████████████" << endl;
        }
        return;
    }

    // delete a value from the table
    void remove(string value) {
        // value found so remove
        if (find(value)) {
            // move the next node up
            HashBucket[foundKey] = emptyString;
            // count value removed
            inserted--;
            // removed notice
            cout << "█ [Success] " << value << " - removed." << endl;
        } else {
            // not found notice
            cout << "█ [Notice] " << value << " - not found." << endl;
        }
        cout << "██████████████████████████████████████████████████████████" << endl;
        return;
    }
};

int main() {
    // instantiate the table
    HashTable Table;
    // program loop (taken and adapted from this weeks module)
    char choice = 'b';
    string aKey;
    // start the program
    cout << "██████████████████████████████████████████████████████████" << endl;
    // interact with user
    while (choice != 'x') {
        // check if the table is full
        if (Table.isFull()) {
            cout << "█ Enter first letter of "
                 << "show, delete, or find: ";
        } else {
            cout << "█ Enter first letter of "
                 << "show, insert, delete, or find: ";
        }
        char choice;
        cin >> choice;
        // clear cin stream
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
            case 's':
                Table.display();
                break;
            case 'i':
                if (Table.isFull()) {
                    cout << "█ Table is full" << endl;
                } else {
                    cout << "█ Enter key value to insert: ";
                    getline(cin, aKey);
                    // now insert the string
                    Table.insert(aKey);
                }
                break;
            case 'd':
                cout << "█ Enter key value to delete: ";
                getline(cin, aKey);
                // now remove the string
                Table.remove(aKey);
                break;
            case 'f':
                cout << "█ Enter key value to find: ";
                getline(cin, aKey);
                // now search for the string
                Table.search(aKey);
                break;
            default:
                cout << "█ Invalid entry" << endl;
                break;
        }
    }
}
