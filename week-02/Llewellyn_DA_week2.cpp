/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Champlain College SDEV-345-81
 *
 * C++ Week 2: Assignment (first semester) - Binary Search (2020/09/11)
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Given the following set of data [4.5,6,1,9.2,4,77,1200,16.4]
 * find the value 9.2 and its index value using binary search.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Written by Llewellyn van der Merwe <llewellyn.vandermerw@mymail.champlain.edu>, September 2020
 * Copyright (C) 2020. All Rights Reserved
 * License GNU/GPL Version 2 or later - http://www.gnu.org/licenses/gpl-2.0.html
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

// Adaption from Starting out with C++ Early Objects (9 Edition)
// IntBinaryTree class - Chapter 19 on page 1130

// Binary Tree Class
class Btree
{
private:
    // insert counter
    int counter;
    // internal object
    struct BtreeNode
    {
        // insert position
        int position;
        // type of value
        int type; // 1 = int; 2 = float;
        // union value
        union {
            int ival;
            float fval;
        } value;
        // tree pointers
        BtreeNode* left;
        BtreeNode* right;
        // tree constructors
        BtreeNode(int value1, int &counter, BtreeNode *left1 = nullptr, BtreeNode *right1 = nullptr) {
            value.ival = value1;
            left = left1;
            right = right1;
            type = 1;
            position = counter++;
        }
        BtreeNode(float value1, int &counter, BtreeNode *left1 = nullptr, BtreeNode *right1 = nullptr) {
            value.fval = value1;
            left = left1;
            right = right1;
            type = 2;
            position = counter++;
        }
    };

    BtreeNode* root; // Pointer to the root of the tree

    // Various helper member functions.
    void insert(BtreeNode *&tree, int num) {
        // If the tree is empty, make a new node and make it
        // the root of the tree
        if (!tree) {
            tree = new BtreeNode(num, counter);
            return;
        }
        // If num is already in tree:
        if (tree->value.ival == num)
            return;
        // The tree is not empty: insert the new node into the
        // left or right subtree
        if ((tree->type == 1 && num < tree->value.ival) || (tree->type == 2 && num < tree->value.fval))
            insert(tree->left, num);
        else
            insert(tree->right, num);
    }
    void insert(BtreeNode *&tree, float num) {
        // If the tree is empty, make a new node and make it
        // the root of the tree
        if (!tree) {
            tree = new BtreeNode(num, counter);
            return;
        }
        // If num is already in tree:
        if (tree->value.fval == num)
            return;
        // The tree is not empty: insert the new node into the
        // left or right subtree
        if ((tree->type == 1 && num < tree->value.ival) || (tree->type == 2 && num < tree->value.fval))
            insert(tree->left, num);
        else
            insert(tree->right, num);
    }
    void destroySubtree(BtreeNode *tree) {
        if (!tree) return;
        destroySubtree(tree->left);
        destroySubtree(tree->right);
        //  Delete the node at the root
        delete tree;
    }
    void remove(BtreeNode *&tree, int num) {
        if (tree == nullptr) return;
        if ((tree->type == 1 && num < tree->value.ival) || (tree->type == 2 && num < tree->value.fval))
            remove(tree->left, num);
        else if ((tree->type == 1 && num > tree->value.ival) || (tree->type == 2 && num > tree->value.fval))
            remove(tree->right, num);
        else
            // We have found the node to delete.
            makeDeletion (tree);
    }
    void remove(BtreeNode *&tree, float num) {
        if (tree == nullptr) return;
        if ((tree->type == 1 && num < tree->value.ival) || (tree->type == 2 && num < tree->value.fval))
            remove(tree->left, num);
        else if ((tree->type == 1 && num > tree->value.ival) || (tree->type == 2 && num > tree->value.fval))
            remove(tree->right, num);
        else
            // We have found the node to delete .
            makeDeletion (tree);
    }
    void makeDeletion(BtreeNode *&tree) {
        // Used to hold node that will be deleted
        BtreeNode *nodeToDelete = tree;

        // Used to locate the point where the
        // left subtree is attached
        BtreeNode *attachPoint;

        if (tree->right == nullptr) {
            // Replace tree with its left subtree
            tree = tree->left ;
        }  else if (tree->left == nullptr) {
            // Replace tree with its right subtree
            tree = tree->right;
        } else {
            // The node has two children
            // Move to right subtree
            attachPoint = tree->right;

            // Locate the smallest node in the right subtree
            // by moving as far to the left as possible
            while (attachPoint->left != nullptr)
                attachPoint = attachPoint->left;

            // Attach the left subtree of the original tree
            // as the left subtree of the smallest node
            // in the right subtree
            attachPoint->left = tree->left;

            // Replace the original tree with its right subtree
            tree = tree->right;
        }
        // Delete root of original tree
        delete nodeToDelete;
    }
    void displayInOrder(BtreeNode *tree) const {
        if (tree) {
            displayInOrder(tree->left);
            if (tree->type == 1) {
                cout << tree->value.ival << " ";
            } else {
                cout << tree->value.fval << " ";
            }
            displayInOrder(tree->right);
        }
    }
    // thanks to https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion/
    void displayIndexOrder(BtreeNode *tree) const {
        int size = counter + 1;
        stack<BtreeNode *> s;
        string order[size];
        BtreeNode *current = tree;

        while(current != NULL || s.empty() == false){
            /* Reach the left most Node of the
           curr Node */
            while (current !=  NULL)
            {
                /* place pointer to a tree node on
                   the stack before traversing
                  the node's left subtree */
                s.push(current);
                current = current->left;
            }

            /* Current must be NULL at this point */
            current = s.top();
            s.pop();

            // add to our order bucket (not ideal...)
            stringstream val;
            if (current->type == 1) {
                val << current->value.ival;
            } else {
                val << current->value.fval;
            }
            order[current->position] = "[" + to_string(current->position) + "]=>" + val.str();
            /* we have visited the node and its
               left subtree.  Now, it's right
               subtree's turn */
            current = current->right;
        }
        // no print out the values
        for (int i = 0; i < size; i++){
            cout << order[i] << " ";
        }
    }

public:
    // These member functions are the public interface.
    // Constructor
    Btree () {
        root = nullptr;
        counter = 0;
    }
    // Destructor
    ~Btree () {
        destroySubtree(root);
    }
    // insert function
    void insert(int num) {
        insert(root, num);
    }
    // insert function
    void insert(float num) {
        insert(root, num);
    }
    // search function
    bool search(int num) const {
        BtreeNode *tree = root;
        while (tree)
        {
            if (tree->value.ival == num)
                return true;
            else if ((tree->type == 1 && num < tree->value.ival) || (tree->type == 2 && num < tree->value.fval))
                tree = tree->left;
            else
                tree = tree->right;
        }
        return  false;
    }
    bool search(float num) const {
        BtreeNode *tree = root;
        while (tree)
        {
            if (tree->value.fval == num)
                return true;
            else if ((tree->type == 1 && num < tree->value.ival) || (tree->type == 2 && num < tree->value.fval))
                tree = tree->left;
            else
                tree = tree->right;
        }
        return  false;
    }
    int searchPosition(int num) const {
        BtreeNode *tree = root;
        while (tree)
        {
            if (tree->value.ival == num)
                return tree->position;
            else if ((tree->type == 1 && num < tree->value.ival) || (tree->type == 2 && num < tree->value.fval))
                tree = tree->left;
            else
                tree = tree->right;
        }
        return -1;
    }
    int searchPosition(float num) const {
        BtreeNode *tree = root;
        while (tree)
        {
            if (tree->value.fval == num)
                return tree->position;
            else if ((tree->type == 1 && num < tree->value.ival) || (tree->type == 2 && num < tree->value.fval))
                tree = tree->left;
            else
                tree = tree->right;
        }
        return  -1;
    }
    // remove a node
    void remove(int num) {
        remove(root, num);
    }
    // remove a node
    void remove(float num) {
        remove(root, num);
    }
    // show in order
    void showInOrder(void) const {
        displayInOrder(root);
    }
    // show in original input order
    void showIndexOrder() const {
        displayIndexOrder(root);
    }
};

int main() {
    Btree tree;
    cout << "Inserting the numbers 4.5, 6, 1, 9.2, 4, 77, 1200, 16.4" << endl;
    tree.insert(4.5f);
    tree.insert(6);
    tree.insert(1);
    tree.insert( 9.2f);
    tree.insert(4);
    tree.insert(77);
    tree.insert(1200);
    tree.insert(16.4f);
    cout << "Here are the values in the tree" << endl;
    tree.showIndexOrder();
    cout << "\nWe found 9.2 at position: " << tree.searchPosition(9.2f) << endl;
    cout << "We found 1200 at position: " << tree.searchPosition(1200) << endl;
    cout << "Deleting 9.2..." << endl;
    tree.remove(9.2f);
    cout << "Deleting 77..." << endl;
    tree.remove(77);
    cout << "Now, here are the nodes values sorted" << endl;
    tree.showInOrder();
    // with removal I am not yet fixing the index ordering ;)
    return 0;
}