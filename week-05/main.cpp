/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Champlain College SDEV-345-81
 *
 * C++ Week 5: Linked Lists (first semester) - linked list program (2020/09/20)
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Write a menu driven program that simulates a simple linked list. The program
 * should give the user the following options and should run in an infinite loop:
 *    1) Insert node
 *    2) Delete node
 *    3) Display list
 *    4) Find node
 *
 * Do not use the C++ Standard Template library.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Written by Llewellyn van der Merwe <llewellyn.vandermerw@mymail.champlain.edu>, October 2020
 * Copyright (C) 2020. All Rights Reserved
 * License GNU/GPL Version 2 or later - http://www.gnu.org/licenses/gpl-2.0.html
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// Adaptation to the code found at
// Week 5: Lectures
// Demonstrates sorted linked list
#include <iostream>

using namespace std;

/////////////////////////////////////////////////////////////
class Node {
public:
    int iData;                                              // data item
    double dData;                                           // data item
    Node *pNext;                                            // ptr to next link in list
//----------------------------------------------------------
    Node(int id, double dd) :                               // constructor
            iData(id), dData(dd), pNext(NULL) {}

//----------------------------------------------------------
    void displayNode()                                      // display ourselves {22, 2.99}
    {
        cout << "{" << iData << ", " << dData << "} ";
    }
//----------------------------------------------------------
};                                                          // end class Node
/////////////////////////////////////////////////////////////
class NodeList {
private:
    Node *pFirst;                                           // ptr to first link on list
public:
//----------------------------------------------------------
    NodeList() : pFirst(NULL)                               // constructor
    {}                                                      // no links on list yet
//----------------------------------------------------------
    ~NodeList(){                                            // destructor
        while(!isEmpty()){                                  // until it's empty,
            removeFirst();                                  // remove it
        }
    }
//----------------------------------------------------------
    bool isEmpty()                                          // true if list is empty
    { return pFirst == NULL; }

//----------------------------------------------------------
                                                            // insert at start of list
    void insertFirst(int id, double dd) {                   // make new link
        Node *pNewNode = new Node(id, dd);
        pNewNode->pNext = pFirst;                           // newNode-->old first
        pFirst = pNewNode;                                  // first-->newNode
    }
//----------------------------------------------------------
    Node *getFirst()                                        // return first link
    { return pFirst; }
//----------------------------------------------------------
    void insert(int key, double dd)                         // insert, in order
    {
        Node* pNewLink = new Node(key, dd);                 // make new link
        Node* pPrevious = NULL;                             // pointer to previous
        Node* pCurrent = pFirst;                            // start at first
                                                            // Look for position prior to the end of the list
        while(pCurrent != NULL && key > pCurrent->iData)    // We sort insert by key and not value
        {
            pPrevious = pCurrent;                           // adjust previous ptr
            pCurrent = pCurrent->pNext;                     // go to next item
        }
                                                            // Insert link the link
        if(pPrevious==NULL)                                 // at beginning of list
            pFirst = pNewLink;                              // first --> newLink
        else                                                // not at beginning
            pPrevious->pNext = pNewLink;                    // old prev --> newLink
        pNewLink->pNext = pCurrent;                         // newLink --> old current
    }                                                       // end insert()
//----------------------------------------------------------
    void removeFirst()                                      // delete first link
    {                                                       // (assumes list not empty)
        Node *pTemp = pFirst;                               // save first
        pFirst = pFirst->pNext;                             // unlink it: first-->old next
        delete pTemp;                                       // delete old first
    }
//-----------------------------------------------------------
    Node* find(int key)                                     // find link with given key
    {                                                       // (assumes non-empty list)
        Node* pCurrent = pFirst;                            // start at 'first'
        while(pCurrent->iData != key)                       // while no match,
        {
            if(pCurrent->pNext == NULL)                     // if end of list,
                return NULL;                                // didn't find it
            else                                            // not end of list,
                pCurrent = pCurrent->pNext;                 // go to next link
        }
        return pCurrent;                                    // found it
    }
//-----------------------------------------------------------
    Node* find(double key)                                  // find link with given key
    {                                                       // (assumes non-empty list)
        Node* pCurrent = pFirst;                            // start at 'first'
        while(pCurrent->dData != key)                       // while no match,
        {
            if(pCurrent->pNext == NULL)                     // if end of list,
                return NULL;                                // didn't find it
            else                                            // not end of list,
                pCurrent = pCurrent->pNext;                 // go to next link
        }
        return pCurrent;                                    // found it
    }
//-----------------------------------------------------------
    bool remove(int key)                                    // remove link with given key
    {                                                       // (assumes non-empty list)
        Node* pCurrent = pFirst;                            // search for link
        Node* pPrevious = pFirst;
        while(pCurrent->iData != key)
        {
            if(pCurrent->pNext == NULL)
                return false;                               // didn't find it
            else
            {
                pPrevious = pCurrent;                       // go to next link
                pCurrent = pCurrent->pNext;
            }
        }                                                   // found it
        if(pCurrent == pFirst)                              // if first link,
            pFirst = pFirst->pNext;                         // change first
        else                                                // otherwise,
            pPrevious->pNext = pCurrent->pNext;             // bypass it
        delete pCurrent;                                    // delete link
        return true;                                        // successful removal
    }
//-----------------------------------------------------------
    bool remove(double value)                               // remove link with given key
    {                                                       // (assumes non-empty list)
        Node* pCurrent = pFirst;                            // search for link
        Node* pPrevious = pFirst;
        while(pCurrent->dData != value)
        {
            if(pCurrent->pNext == NULL)
                return false;                               // didn't find it
            else
            {
                pPrevious = pCurrent;                       // go to next link
                pCurrent = pCurrent->pNext;
            }
        }                                                   // found it
        if(pCurrent == pFirst) {                            // if first link,
            if (pCurrent->pNext == NULL) {
                pFirst = pFirst->pNext;                     // change first
            } else {
                pFirst = NULL;                              // empty the list
            }
        } else {                                            // otherwise,
            pPrevious->pNext = pCurrent->pNext;             // bypass it
        }
        delete pCurrent;                                    // delete link
        return true;                                        // successful removal
    }
//----------------------------------------------------------
    void displayList() {
        cout << "List (first-->last): ";
        Node *pCurrent = pFirst;                            // start at beginning of list
        while (pCurrent != NULL)                            // until end of list,
        {
            pCurrent->displayNode();                        // print data
            pCurrent = pCurrent->pNext;                     // move to next link
        }
        cout << endl;
    }
//----------------------------------------------------------
};                                                          // end class NodeList
/////////////////////////////////////////////////////////////
void getUserInput(int &action, const string& act){          // get the user input
    cin.clear();
    while (true) {
        cout << act << " a node by key or value." << endl;
        cout << "1] Key" << endl;                           // Select to find by key
        cout << "2] Value" << endl;                         // Select to find by value
        cout << "[1/2]: ";
        cin >> action;
        if (!cin.fail() && (action == 1 || action == 2)) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Selection must be between 1 or 2, lets try again." << endl;
    }
}
void getUserInput(const string& question, int &key){
    cin.clear();
    while (true) {
        cout << question << endl;
        cout << "[integer]: ";                              // get only an integer
        cin >> key;
        if (!cin.fail() && key > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "The key must be an integers above zero, lets try again." << endl;
    }
}
void getUserInput(const string& question, double &value){
    cin.clear();
    while (true) {
        cout << question << endl;
        cout << "[double]: ";
        cin >> value;                                       // get only an double
        if (!cin.fail() && value > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "The value must be an double above zero, lets try again." << endl;
    }
}
void displayMenu(int& action, NodeList& theList){
    while (true) {
        if (theList.isEmpty()) {
            cout << "Your link-list is empty, insert your first node." << endl;
            action = 1;
            break;
        }
        cin.clear();
        cout << "1] Insert Node" << endl;               // Select to insert node
        cout << "2] Delete Node" << endl;               // Select to delete node
        cout << "3] Display List" << endl;              // Select to display list
        cout << "4] Find node" << endl;                 // Select to display list
        cout << "[1-4]: ";
        cin >> action;
        action = (int) action;
        if (!cin.fail() && action > 0 && action < 5) {
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Selection must be between 1 and 4, lets try again." << endl;
    }
}
/////////////////////////////////////////////////////////////
int main() {
    NodeList theList;                                       // make new list
    int action;                                             // the driver action
    int idata;                                              // the driver int Data
    double ddata;                                           // the driver double Data
    cout << "Demonstrating the infinite link-list program" << endl; // little notice
    while (true) {
        displayMenu(action, theList);                 // display the menu
        if (action == 1){                                   // insert a node
            getUserInput("Enter a key", idata);
            getUserInput("Enter a value", ddata);
            theList.insert(idata, ddata);
            cout << "A node with this key(" << idata << ") and this value(" << ddata << ") was added." << endl;
        } else if (action == 2){                            // delete node
            getUserInput(action, "Delete");
            if (action == 1) {
                getUserInput("Enter a key to delete", idata);
                if (theList.remove(idata)){
                    cout << "The first node with this key(" << idata << ") was removed." << endl;
                } else {
                    cout << "A node with this key(" << idata << ") was not found." << endl;
                }
            } else if (action == 2) {
                getUserInput("Enter a value to delete", ddata);
                if (theList.remove(ddata)){
                    cout << "The first node with this value(" << ddata << ") was removed." << endl;
                } else {
                    cout << "A node with this value(" << ddata << ") was not found." << endl;
                }
            }
        } else if (action == 3){                             // display list
            theList.displayList();
        } else if (action == 4){                             // find node
            getUserInput(action, "Find");
            if (action == 1) {
                getUserInput("Enter a key to find", idata);
                Node* found = theList.find(idata);
                if (found){
                    cout << "The first node with this key(" << idata << ") was found. ";
                    found->displayNode();
                    cout << endl;
                } else {
                    cout << "A node with this key(" << idata << ") was NOT found." << endl;
                }
            } else if (action == 2) {
                getUserInput("Enter a value to find", ddata);
                Node* found = theList.find(ddata);
                if (found){
                    cout << "The first node with this value(" << ddata << ") was found. ";
                    found->displayNode();
                    cout << endl;
                } else {
                    cout << "A node with this value(" << ddata << ") was NOT found." << endl;
                }
            }
        } else {
            break;                                           // just to remove endless loop warning (should never happen)
        }
    }
    return 0;
}                                                            // end main()