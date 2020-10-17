/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Champlain College SDEV-345-81
 *
 * C++ Week 6: Circular or Doubly Linked Lists (first semester) - Linked Lists program (2020/10/16)
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Write a menu driven program that creates a doubly linked list.
 * The program should give the user the following options and should
 * run in an infinite loop:
 *    1) Insert first node
 *    2) Insert last node
 *    3) Delete first node
 *    4) Delete last node
 *    5) Display list forward
 *    6) Display list backwards
 *
 * Do not use the C++ Standard template library.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Written by Llewellyn van der Merwe <llewellyn.vandermerw@mymail.champlain.edu>, October 2020
 * Copyright (C) 2020. All Rights Reserved
 * License GNU/GPL Version 2 or later - http://www.gnu.org/licenses/gpl-2.0.html
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// Adaptation to the code found at
// Week 7: Lecture 4 - Doubly Linked CPP
// Demonstrates Doubly Linked Lists
#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////
class Link
{
public:
    double dData;                            // data item
    Link* pNext;                             // next link in list
    Link* pPrevious;                         // previous link in list
public:
//-------------------------------------------------------------
    Link(double dd) :                        // constructor
            dData(dd), pNext(NULL), pPrevious(NULL)
    {  }
//-------------------------------------------------------------
    void displayLink()                       // display this link
    { cout << dData << " "; }
//-------------------------------------------------------------
};  //end class Link
////////////////////////////////////////////////////////////////
class DoublyLinkedList
{
private:
    Link* pFirst;                            // pointer to first item
    Link* pLast;                             // pointer to last item
public:
//-------------------------------------------------------------
    DoublyLinkedList() :                     // constructor
            pFirst(NULL), pLast(NULL)
    {  }
//-------------------------------------------------------------
    ~DoublyLinkedList()                      // destructor (deletes links)
    {
        Link* pCurrent = pFirst;             // start at beginning of list
        while(pCurrent != NULL)              // until end of list,
        {
            Link* pOldCur = pCurrent;        // save current link
            pCurrent = pCurrent->pNext;      // move to next link
            delete pOldCur;                  // delete old current
        }
    }
//-------------------------------------------------------------
    bool isEmpty()                           // true if no links
    { return pFirst==NULL; }
//-------------------------------------------------------------
    void insertFirst(double dd)              // insert at front of list
    {
        Link* pNewLink = new Link(dd);       // make new link

        if( isEmpty() )                      // if empty list,
            pLast = pNewLink;                // newLink <-- last
        else
            pFirst->pPrevious = pNewLink;    // newLink <-- old first
        pNewLink->pNext = pFirst;            // newLink --> old first
        pFirst = pNewLink;                   // first --> newLink
    }
//-------------------------------------------------------------
    void insertLast(double dd)               // insert at end of list
    {
        Link* pNewLink = new Link(dd);       // make new link
        if( isEmpty() )                      // if empty list,
            pFirst = pNewLink;               // first --> newLink
        else
        {
            pLast->pNext = pNewLink;         // old last --> newLink
            pNewLink->pPrevious = pLast;     // old last <-- newLink
        }
        pLast = pNewLink;                    // newLink <-- last
    }
//-------------------------------------------------------------
    void removeFirst()                       // remove first link
    {                                        // (assumes non-empty list)
        Link* pTemp = pFirst;
        if(pFirst->pNext == NULL)            // if only one item
            pLast = NULL;                    // null <-- last
        else
            pFirst->pNext->pPrevious = NULL; // null <-- old next
        pFirst = pFirst->pNext;              // first --> old next
        delete pTemp;                        // delete old first
    }
//-------------------------------------------------------------
    void removeLast()                        // remove last link
    {                                        // (assumes non-empty list)
        Link* pTemp = pLast;
        if(pFirst->pNext == NULL)            // if only one item
            pFirst = NULL;                   // first --> null
        else
            pLast->pPrevious->pNext = NULL;  // old previous --> null
        pLast = pLast->pPrevious;            // old previous <-- last
        delete pTemp;                        // delete old last
    }
//-------------------------------------------------------------
    void displayForward()
    {
        cout << "List (first-->last): ";
        Link* pCurrent = pFirst;             // start at beginning
        while(pCurrent != NULL)              // until end of list,
        {
            pCurrent->displayLink();         // display data
            pCurrent = pCurrent->pNext;      // move to next link
        }
        cout << endl;
    }
//-------------------------------------------------------------
    void displayBackward()
    {
        cout << "List (last-->first): ";
        Link* pCurrent = pLast;              // start at end
        while(pCurrent != NULL)              // until start of list,
        {
            pCurrent->displayLink();         // display data
            pCurrent = pCurrent->pPrevious;  // go to previous link
        }
        cout << endl;
    }
//-------------------------------------------------------------
};  //end class DoublyLinkedList
////////////////////////////////////////////////////////////////
void getUserInput(const string &question, double &value) {
    cin.clear();
    while (true) {
        cout << question << endl;
        cout << "[value]: ";
        cin >> value;                         // get only an double
        if (!cin.fail() && value > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "The value must be an double above zero, lets try again." << endl;
    }
}
void displayMenu(int &action) {
    while (true) {
        cin.clear();
        cout << "   1] Insert first node" << endl;
        cout << "   2] Insert last node" << endl;
        cout << "   3] Delete first node" << endl;
        cout << "   4] Delete last node" << endl;
        cout << "   5] Display list forward" << endl;
        cout << "   6] Display list backwards" << endl;
        cout << "   [1-6]: ";
        cin >> action;
        action = (int) action;
        if (!cin.fail() && action > 0 && action < 7) {
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Selection must be between 1 and 6, lets try again." << endl;
    }
}
////////////////////////////////////////////////////////////////
int main()
{
    DoublyLinkedList theList;                 // make a new list
    int action;                               // the driver action
    double data;                              // the driver double Data
    cout << "Demonstrating the infinite doubly linked list program" << endl; // little notice
    while (true) {
        displayMenu(action);               // display the menu
        if (action == 1) {                    // Insert first node
            getUserInput("Enter a number", data);
            theList.insertFirst(data);
        } else if (action == 2) {             // Insert last node
            getUserInput("Enter a number", data);
            theList.insertLast(data);
        } else if (action == 3) {             // Delete first node
            if (!theList.isEmpty()) {
                theList.removeFirst();
            } else {
                cout << "The doubly linked list is empty, can not remove any items." << endl;
            }
        } else if (action == 4) {             // Delete last node
            if (!theList.isEmpty()) {
                theList.removeLast();
            } else {
                cout << "The doubly linked list is empty, can not remove any items." << endl;
            }
        } else if (action == 5) {             // Display list forward
            if (!theList.isEmpty()) {
                theList.displayBackward();
            } else {
                cout << "The doubly linked list is empty, no items to display backward." << endl;
            }
        } else if (action == 6) {             // Display list backwards
            if (!theList.isEmpty()) {
                theList.displayForward();
            } else {
                cout << "The doubly linked list is empty, no items to display forward." << endl;
            }
        } else {
            break;       // just to remove endless loop warning (should never happen)
        }
    }
    return 0;
}
