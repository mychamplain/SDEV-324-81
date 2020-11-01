//SDEV345-81
//Kodi Lein
#include <iostream> 
using namespace std;

/*Node Class*/
class Node
{
public:
    int data;
    Node* next;
    Node* prev;
};

/*Swap elements*/
void swap(int* a, int* b)
{
    int t = *a; *a = *b; *b = t;
}

/*Find last node in list*/
Node* lastNode(Node* root)
{
    while (root && root->next)
        root = root->next;
    return root;
}

/*Define pivot point and moves smaller elements to left, larger to right*/
Node* partition(Node* l, Node* h)
{
    //h = pivot point
    int x = h->data;

    Node* i = l->prev;

    for (Node* j = l; j != h; j = j->next)
    {
        if (j->data <= x)
        {
            i = (i == NULL) ? l : i->next;

            swap(&(i->data), &(j->data));
        }
    }
    i = (i == NULL) ? l : i->next;
    swap(&(i->data), &(h->data));
    return i;
}

/*Quicksort function*/
void QS(Node* l, Node* h)
{
    if (h != NULL && l != h && l != h->next)
    {
        Node* p = partition(l, h);
        QS(l, p->prev);
        QS(p->next, h);
    }
}

//Calls function quicksort 
void quickSort(Node* head)
{
    // Find last node  
    Node* h = lastNode(head);

    // Call the recursive QuickSort  
    QS(head, h);
}
 
void printList(Node* head)
{
    while (head)
    {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

/*Insert Node*/
void push(Node** head_ref, int new_data)
{
    Node* new_node = new Node;
    new_node->data = new_data;

    new_node->prev = NULL;

    new_node->next = (*head_ref);

    if ((*head_ref) != NULL) (*head_ref)->prev = new_node;

    (*head_ref) = new_node;
}

/*MAIN*/
int main()
{
    Node* a = NULL;
    push(&a, 421003);
    push(&a, 100298);
    push(&a, 494002);
    push(&a, 93);
    push(&a, 3394);
    push(&a, 21093);
    push(&a, 3949500);
    push(&a, 29100);
    push(&a, 6493939);
    push(&a, 202814);
    push(&a, 506984);
    push(&a, 2);
    push(&a, 665778);

    cout << "Linked List before sorting \n";
    printList(a);

    quickSort(a);
    
    cout << "\nLinked List after sorting \n";
    printList(a);

    return 0;
}