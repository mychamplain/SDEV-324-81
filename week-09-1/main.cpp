// Adaptation to the code found at
// Week 5: Lectures
// Demonstrates sorted linked list
#include <iostream>

using namespace std;

/////////////////////////////////////////////////////////////
class Node {
public:
    int filenumber;                    // the file number
    Node *pNext;                       // ptr to next link in list
//----------------------------------------------------------
    Node(int value) :                     // constructor
            filenumber(value), pNext(NULL) {}

//----------------------------------------------------------
    void displayNode()                 // display ourselves {22}
    {
        cout << "{" << filenumber << "} ";
    }
//----------------------------------------------------------
};                                     // end class Node
/////////////////////////////////////////////////////////////
class NodeList {
private:
    Node *pFirst;                      // ptr to first link on list
public:
//----------------------------------------------------------
    NodeList() : pFirst(NULL)          // constructor
    {}                                 // no links on list yet
//----------------------------------------------------------
    ~NodeList(){                       // destructor
        while(!isEmpty()){             // until it's empty,
            removeFirst();             // remove it
        }
    }
//----------------------------------------------------------
    bool isEmpty()                     // true if list is empty
    { return pFirst == NULL; }
//----------------------------------------------------------
    Node *getFirst()                  // return first link
    { return pFirst; }
//----------------------------------------------------------
    void insert(int value)              // insert, in order
    {
        Node* pNewLink = new Node(value); // make new link
        Node* pPrevious = NULL;       // pointer to previous
        Node* pCurrent = pFirst;      // start at first
        // Look for position prior to the end of the list
        // We quicksort insert by value
        while(pCurrent != NULL && value > pCurrent->filenumber)
        {
            pPrevious = pCurrent;    // adjust previous ptr
            pCurrent = pCurrent->pNext; // go to next item
        }
        // Insert link the link
        if(pPrevious==NULL)           // at beginning of list
            pFirst = pNewLink;        // first --> newLink
        else                          // not at beginning
            pPrevious->pNext = pNewLink; // old prev --> newLink
        pNewLink->pNext = pCurrent;   // newLink --> old current
    }                                 // end insert()
//----------------------------------------------------------
    void removeFirst()                // delete first link
    {                                 // (assumes list not empty)
        Node *pTemp = pFirst;         // save first
        pFirst = pFirst->pNext;       // unlink it: first-->old next
        delete pTemp;                 // delete old first
    }
//----------------------------------------------------------
    void displayList() {
        cout << "List (value): ";
        Node *pCurrent = pFirst;      // start at beginning of list
        while (pCurrent != NULL)      // until end of list,
        {
            pCurrent->displayNode();  // print data
            pCurrent = pCurrent->pNext; // move to next link
        }
        cout << endl;
    }
//----------------------------------------------------------
};                                    // end class NodeList
/////////////////////////////////////////////////////////////
int main() {
    NodeList theList;                 // make new list
    cout << "Demonstrating the sorted link-list program" << endl;
    theList.insert(421003);
    theList.insert(100298);
    theList.insert(494002);
    theList.insert(93);
    theList.insert(3994);
    theList.insert(21093);
    theList.insert(3949500);
    theList.insert(29100);
    theList.insert(6493939);
    theList.insert(202814);
    theList.insert(506984);
    theList.insert(2);
    theList.insert(665778);
    cout << " This is all the values that are now in the linked list" << endl;
    theList.displayList();
    return 0;
}