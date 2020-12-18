/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Champlain College SDEV-345-81
 *
 * C++ Week 15 Final Project - (2020/12/13)
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Code must be object oriented
 * Code must be thoroughly commented
 * The project shall use the queue data structure learned in the course.
 * Do not use the queue library.
 *
 * A supermarket has 9 cashiers. Customers arrive and leave at random time intervals.
 * Use 0-5 seconds for this project. Make sure the customers arrive faster than they depart
 * so that the queues fill up. The goal of the program is to put the next arriving customer
 * in the shortest queue out of the 9 cashier queues. Your program will need to loop infinitely
 * to simulate the passing of a certain amount of time. I suggest looping the program every second
 * and clearing the screen and displaying all queues. Use a simple "for loop" as a delay.
 * Also use asterisks (*) to represent customers.
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
#include <string>
#include <random>
#include <thread>

using namespace std;

//////// The Link Class /////////////////////////////////////////
class Link {
public:
    string dData;                      // data item
    Link *pNext;                       // ptr to next link in list
//-------------------------------------------------------------
    Link(string d) : dData(d), pNext(nullptr)  // constructor
    {}

//-------------------------------------------------------------
    void displayLink()                 // display this link
    { cout << dData; }
//-------------------------------------------------------------
};

//////// The Last in First Out Class - Queue ////////////////////
class LastInFirstOut {
private:
    Link *pFirst;                      // ptr to first link
    Link *pLast;                       // ptr to last link
    int Size = 0;                      // total in queue
public:
//-------------------------------------------------------------
    LastInFirstOut() : pFirst(nullptr), pLast(nullptr)  //constructor
    {}

//-------------------------------------------------------------
    ~LastInFirstOut()                   // destructor
    {                                   // (deletes all links)
        Link *pCurrent = pFirst;        // start at beginning
        while (pCurrent != nullptr)     // until end of list,
        {
            Link *pTemp = pCurrent;     // remember current
            pCurrent = pCurrent->pNext; // move to next link
            delete pTemp;               // delete old current
        }
    }

//-------------------------------------------------------------
    bool isEmpty()                      // true if no links
    { return pFirst == nullptr; }

//-------------------------------------------------------------
    int size()                          // the size of the queue
    { return Size; }

//-------------------------------------------------------------
    void insertLast(string dd)          // insert at end of list
    {
        Link *pNewLink = new Link(dd);  // make new link
        if (isEmpty())                  // if empty list,
            pFirst = pNewLink;          // first --> newLink
        else
            pLast->pNext = pNewLink;    // old last --> newLink
        pLast = pNewLink;               // newLink <-- last

        Size++;                         // count insert
    }

//-------------------------------------------------------------
    void removeFirst()                    // delete first link
    {
        if (!isEmpty()) {
            Size--;                       // count insert removed
            Link *pTemp = pFirst;         // remember first link
            if (pFirst->pNext == nullptr) // if only one item
                pLast = nullptr;          // null <-- last
            pFirst = pFirst->pNext;       // first --> old next
            delete pTemp;                 // delete the link
        }
    }

//-------------------------------------------------------------
    void displayList() {
        Link *pCurrent = pFirst;        // start at beginning
        while (pCurrent != nullptr)     // until end of list,
        {
            pCurrent->displayLink();    // print data
            pCurrent = pCurrent->pNext; // move to next link
        }
    }
//-------------------------------------------------------------
};

//////// The Cashier Class //////////////////////////////////////
class Cashier {
private:
    LastInFirstOut activeQueue;          // the active queue
    int counter = 0;                     // the leaving queue counter

//-------------------------------------------------------------
    int _rndm(int min, int max)          // set some random number
    {
        random_device rd;
        mt19937 get_card(rd());
        uniform_int_distribution<> my_random(min, max);
        return my_random(get_card);
    }

//--------------------------------------------------------------
    void payed()                         // payed client leaves front of queue
    {
        // remove from queue
        activeQueue.removeFirst();
        // add to leaving queue
        counter++;
    }

//--------------------------------------------------------------
    bool hasClient()                     // true if has client
    { return !activeQueue.isEmpty(); }

public:
//--------------------------------------------------------------
    int queued()                        // number of clients in queue
    { return activeQueue.size(); }

//--------------------------------------------------------------
    void arrive()                       // new client arrive at rear of queue
    { activeQueue.insertLast("*"); }

    void arrive(int number)             // new clients arrive at rear of queue
    {
        for (int n = 0; n < number; n++)
            arrive();
    }

//--------------------------------------------------------------
    void process()                       // process client
    {
        int done = _rndm(0, 1);
        // if 1 remove one if not empty
        if (done == 1 && hasClient()) {
            // client paid and is leaving
            payed();
        }
    }

//--------------------------------------------------------------
    void camera(int spacer) {
        // remove the number in queue
        spacer = spacer - queued();
        // now add the spacing
        if (spacer > 0)
            cout << string(spacer, ' ');
        // display clients waiting
        activeQueue.displayList();
        // show clients leaving
        if (counter == 0) {
            cout << "[Cashier]" << endl;
        } else {
            cout << "[Cashier] (" << counter << ")->clients-served" << endl;
        }
    }

//--------------------------------------------------------------
};

//////// The Shop Class //////////////////////////////////////
class Shop {
private:
    bool open;                   // while the shop is open (true)
    bool limit = true;          // turn on limit (false makes shop infinite)
    int dailyLimit = 3000;     // the shops daily limit
    int speed = 100;            // the shops processing speed
    int longestQueue = 1;        // the longest queue
    int clientsIn = 0;           // number of clients in shop
    int clientsTotal = 0;        // number of total clients
    const static int tillN = 10;  // the number of cashiers in shop
    Cashier Cashiers[tillN];     // all cashiers

//--------------------------------------------------------------
    int getNextQueue()                     // get the next queue
    {
        int smallest = dailyLimit * 100;   // highest number allowed in the shop
        int counter = 0;                   // counter to check empty cashiers
        int key = _rndm(0, 9);    // array key to return
        int size;                          // just a queued size
        clientsIn = 0;                     // reset the clients inside store
        // we go over all cashiers
        for (int t = 0; t < tillN; t++) {
            // get the queued size
            size = Cashiers[t].queued();
            // count how many is still in shop
            clientsIn += size;
            // check the smallest
            if (size <= smallest) {
                smallest = size;
                key = t;
                // at each zero we count
                if (size == 0) {
                    counter++;
                }
            }
            // also set longest
            if (size > longestQueue) {
                longestQueue = size;
            }
        }
        // we check if all cashiers are empty
        if (counter == tillN) {
            return _rndm(0, counter);
        }
        // return smallest
        return key;
    }

//-------------------------------------------------------------
    int _rndm(int min, int max)          // set some random number
    {
        random_device rd;
        mt19937 get_card(rd());
        uniform_int_distribution<> my_random(min, max);
        return my_random(get_card);
    }

//--------------------------------------------------------------
    void arrivals()                       // arriving client
    {
        int arrived = _rndm(0, 7);
        int key, arrivals;
        // if more then one we have new arrival
        if (arrived > 3) {
            // when clients arrive we must queue them
            for (int c = 0; c < arrived; c++) {
                // get smallest queue
                key = getNextQueue();
                // get the number of arrivals
                arrivals = _rndm(1, 2);
                // add to total
                clientsTotal += arrivals;
                // add the new arrivals also
                clientsIn += arrivals;
                // add the arrival
                Cashiers[key].arrive(arrivals);
            }
        }
    }

//--------------------------------------------------------------
    void clearScreen() {                 // method to clear the screen
        // not ideal... but okay
        cout << string(100, '\n');
        // I could also use this method
        // https://github.com/Llewellynvdm/game-of-life/blob/master/src/Util.cpp#L282
    }

//--------------------------------------------------------------
    void displayCameras()               // display all queues
    {
        // show the total number of clients currently in shop
        cout << "==========================================================" << endl;
        cout << "== Clients In Store: " << clientsIn << endl;
        cout << "==========================================================" << endl;
        // we go over all cashier cameras
        for (int view = 0; view < tillN; view++) {
            // check who is in the queue
            Cashiers[view].camera(longestQueue);
            // check if we have to process clients
            Cashiers[view].process();
        }
        cout << "==========================================================" << endl;
        cout << "== Total Clients: " << clientsTotal << endl;
        cout << "==========================================================" << endl;
        // give final notice
        if (!open && clientsIn == 0) {
            cout << "== Supermarket Closed :) " << endl;
            cout << "==========================================================" << endl;
            cout << string(2, '\n');
        } else {
            cout << string(4, '\n');
        }
    }

public:
//-------------------------------------------------------------
    void watchCashiers() {
        // shop is open
        open = true;
        // this will run infinite
        while (open || clientsIn > 0) {
            // check if we are over daily limit
            // then we just help those still in shop
            if (clientsTotal >= dailyLimit && limit) {
                // close the shop now
                open = false;
            }
            // always clear the last view
            clearScreen();
            // start the shop view
            cout << "==========================================================" << endl;
            // are we using the limited version
            if (limit) {
                // we run until we have served daily limit of clients
                cout << "== Supermarket Client Limit - " << dailyLimit << " Per/Day " << endl;
            } else {
                // we run until we have served daily limit of clients
                cout << "== Infinite Supermarket" << endl;
            }
            // only allow arrivals if shop is open
            if (open) {
                // check if we new arrivals
                arrivals();
            } else {
                // update counters
                getNextQueue();
            }
            // display clients waiting
            displayCameras();
            // slow down a little
            this_thread::sleep_for(chrono::milliseconds(speed));
        }
    }
//-------------------------------------------------------------
};

//////// Main //////////////////////////////////////////////////
int main() {
    Shop supermarket;             // the new shop
    supermarket.watchCashiers();  // the view of the cashiers
    return 0;
}
