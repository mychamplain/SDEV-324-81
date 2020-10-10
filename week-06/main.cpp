/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Champlain College SDEV-345-81
 *
 * C++ Week 6: Stacks and Queues (first semester) - Linked Lists program (2020/10/12)
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Write a menu driven program that creates a queued linked list.
 * The program should give the user the following options and should
 * run in an infinite loop:
 *    1) Is queue empty?
 *    2) Pop front
 *    3) Push back
 *    4) Display Queue
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
// Week 6: Lecture 4 - Queue
// Demonstrates queue implemented as linked list
#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////
class Link {
public:
    double dData;                      // data item
    Link *pNext;                       // ptr to next link in list
//-------------------------------------------------------------
    Link(double d) : dData(d), pNext(NULL)  // constructor
    {}

//-------------------------------------------------------------
    void displayLink()                 // display this link
    { cout << dData << " "; }
//-------------------------------------------------------------
};  //end class Link
////////////////////////////////////////////////////////////////
class FirstLastList {
private:
    Link *pFirst;                      // ptr to first link
    Link *pLast;                       // ptr to last link
public:
//-------------------------------------------------------------
    FirstLastList() : pFirst(NULL), pLast(NULL)  //constructor
    {}

//-------------------------------------------------------------
    ~FirstLastList()                    // destructor
    {                                   // (deletes all links)
        Link *pCurrent = pFirst;        // start at beginning
        while (pCurrent != NULL)        // until end of list,
        {
            Link *pTemp = pCurrent;     // remember current
            pCurrent = pCurrent->pNext; // move to next link
            delete pTemp;               // delete old current
        }
    }

//-------------------------------------------------------------
    bool isEmpty()                      // true if no links
    { return pFirst == NULL; }

//-------------------------------------------------------------
    void insertLast(double dd)          // insert at end of list
    {
        Link *pNewLink = new Link(dd);  // make new link
        if (isEmpty())                  // if empty list,
            pFirst = pNewLink;          // first --> newLink
        else
            pLast->pNext = pNewLink;    // old last --> newLink
        pLast = pNewLink;               // newLink <-- last
    }

//-------------------------------------------------------------
    double removeFirst()                // delete first link
    {                                   // (assumes non-empty list)
        Link *pTemp = pFirst;           // remember first link
        double temp = pFirst->dData;
        if (pFirst->pNext == NULL)      // if only one item
            pLast = NULL;               // null <-- last
        pFirst = pFirst->pNext;         // first --> old next
        delete pTemp;                   // delete the link
        return temp;
    }

//-------------------------------------------------------------
    void displayList() {
        Link *pCurrent = pFirst;        // start at beginning
        while (pCurrent != NULL)        // until end of list,
        {
            pCurrent->displayLink();    // print data
            pCurrent = pCurrent->pNext; // move to next link
        }
        cout << endl;
    }
//-------------------------------------------------------------
};  //end class FirstLastList
////////////////////////////////////////////////////////////////
class LinkQueue {
private:
    FirstLastList theList;
public:
//--------------------------------------------------------------
    bool isEmpty()                       // true if queue is empty
    { return theList.isEmpty(); }

//--------------------------------------------------------------
    void push(double j)                  // insert, rear of queue
    { theList.insertLast(j); }

//--------------------------------------------------------------
    double pop()                         // remove, front of queue
    { return theList.removeFirst(); }

//--------------------------------------------------------------
    void display() {
        cout << "Queue (front<--back): ";
        theList.displayList();
    }
//--------------------------------------------------------------
};  //end class LinkQueue
/////////////////////////////////////////////////////////////
void getUserInput(const string &question, double &value) {
    cin.clear();
    while (true) {
        cout << question << endl;
        cout << "[value]: ";
        cin >> value;                            // get only an double
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
        cout << "   1] Is queue empty?" << endl; // Check if queue is empty?
        cout << "   2] Pop front" << endl;       // Select to delete node
        cout << "   3] Push back" << endl;       // Select to display list
        cout << "   4] Display Queue" << endl;   // Select to display list
        cout << "   [1-4]: ";
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

////////////////////////////////////////////////////////////////
int main() {
    LinkQueue theQueue;                          // make new list queue
    int action;                                  // the driver action
    double data;                                 // the driver double Data
    cout << "Demonstrating the infinite queue link-list program" << endl; // little notice
    while (true) {
        displayMenu(action);                   // display the menu
        if (action == 1) {                        // check if queue is empty
            if (theQueue.isEmpty()) {
                cout << "Yes, the queue is empty." << endl;
            } else {
                cout << "No, the queue has values." << endl;
            }
        } else if (action == 2) {                 // pop a value from the stack
            if (theQueue.isEmpty()) {
                cout << "The queue is empty and no value could be pop'ed." << endl;
            } else {
                data = theQueue.pop();
                cout << "A value(" << data << ") was pop'ed from the stack." << endl;
            }
        } else if (action == 3) {                 // push a value to the back
            bool wasEmpty = theQueue.isEmpty();
            getUserInput("Enter a number", data);
            theQueue.push(data);
            if (wasEmpty){
                cout << "A value(" << data << ") was added to the queue." << endl;
            } else {
                cout << "A value(" << data << ") was added to the back of the queue." << endl;
            }
        } else if (action == 4) {                 // display list
            if (theQueue.isEmpty()) {
                cout << "The queue is empty." << endl;
            } else {
                theQueue.display();
            }
        } else {
            break;       // just to remove endless loop warning (should never happen)
        }
    }
    return 0;
}  //end main()