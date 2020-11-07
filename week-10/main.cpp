/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Champlain College SDEV-345-81
 *
 * C++ Week 9: Trees (first semester) - (2020/11/7)
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Write a menu driven program that creates a binary tree. The program should give the user the
 * following options and should run in an infinite loop:
 *
 * 1) Insert node
 * 2) Find node
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Written by Llewellyn van der Merwe <llewellyn.vandermerw@mymail.champlain.edu>, November 2020
 * Copyright (C) 2020. All Rights Reserved
 * License GNU/GPL Version 2 or later - http://www.gnu.org/licenses/gpl-2.0.html
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <vector>

using namespace std;

// Binary Tree Class
// Adapted from Chapter 19
// IntBinaryTree class on page 1130
// Starting out with C++ Early Objects (9 Edition)
class Btree
{
private:
    // the node object
    struct BtreeNode
    {
        double value;
        BtreeNode* left;
        BtreeNode* right;
        BtreeNode(double value_, BtreeNode *left_ = nullptr, BtreeNode *right_ = nullptr) {
            value = value_;
            left = left_;
            right = right_;
        }
    };
    // Pointer to the root of the tree
    BtreeNode* root;
    // search for value
    bool search(double num, BtreeNode *tree) const {
        // If the tree is empty
        if (!tree) {
            return false;
        }
        // found the value
        if (tree->value == num)
            return true;
        else if (num < tree->value)
            // recursive search
            search(num, tree->left);
        else
            // recursive search
            search(num, tree->right);
    }
    // clear the memory
    void destroySubtree(BtreeNode *tree) {
        if (!tree) return;
        destroySubtree(tree->left);
        destroySubtree(tree->right);
        //  Delete the node at the root
        delete tree;
    }
    // display the tree
    // Adapted from https://stackoverflow.com/a/51730733/1429677
    void display(const std::string& prefix, const BtreeNode* node, bool isLeft)
    {
        if( node != nullptr ) {
            // print the prefix
            cout << prefix;
            cout << (isLeft ? "├──" : "└──" );
            // print the value of the node
            cout << node->value << endl;
            // enter the next tree level - left and right branch
            display( prefix + (isLeft ? "│   " : "    "), node->left, true);
            display( prefix + (isLeft ? "│   " : "    "), node->right, false);
        }
    }

public:
    // These member functions are the public interface.
    // Constructor
    Btree () {
        root = nullptr;
    }
    // Destructor
    ~Btree () {
        destroySubtree(root);
    }
    // check if the tree is empty
    bool isEmpty(){
        if (root == nullptr)
            return true;
        return false;
    }
    // insert function
    void insert(double num) {
        BtreeNode *tree = root;
        // if the tree is empty
        if (tree == nullptr) {
            root = new BtreeNode(num);
            return;
        }
        // tree not empty we add leaves
        while (true)
        {
            if (tree->value == num) {
                return;
            } else if (num < tree->value) {
                if (tree->left == nullptr){
                    tree->left = new BtreeNode(num);
                    return;
                } else {
                    tree = tree->left;
                }
            } else {
                if (tree->right == nullptr){
                    tree->right = new BtreeNode(num);
                    return;
                } else {
                    tree = tree->right;
                }
            }
        }
    }
    // search function
    bool search(double num) const {
        search(num, root);
    }
    // display the binary tree
    void display() {
        display("", root, false);
    }
};
// get the user input
void getUserInput(const string &question, double &value) {
    cin.clear();
    while (true) {
        cout << question << endl;
        cout << "[value]: ";
        // get only an double
        cin >> value;
        if (!cin.fail() && value > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "The value must be an double above zero, lets try again." << endl;
    }
}
// show the menu
void displayMenu(int &action) {
    while (true) {
        cin.clear();
        cout << "   1] Insert node" << endl;
        cout << "   2] Find node" << endl;
        cout << "   [1-2]: ";
        cin >> action;
        action = (int) action;
        if (!cin.fail() && action > 0 && action < 3) {
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Selection must be between 1 and 2, lets try again." << endl;
    }
}
// check if tree is to be displayed
void displayTree(int &display) {
    while (true) {
        cin.clear();
        cout << "Welcome to a binary tree program" << endl;
        cout << "   Do you want to see the tree" << endl;
        cout << "   1] Yes" << endl;
        cout << "   2] No" << endl;
        cout << "   [1-2]: ";
        cin >> display;
        display = (int) display;
        if (!cin.fail() && display > 0 && display < 3) {
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Selection must be between 1 and 2, lets try again." << endl;
    }
}
// the main function to he program
int main() {
    Btree tree;
    // the driver action
    int action;
    // the driver display
    int display;
    // the driver double Data
    double data;
    // ask if we should display the tree
    displayTree(display);
    while (true) {
        // check if we have a tree data structure
        if (!tree.isEmpty() && display == 1){
            // display the tree
            tree.display();
        }
        // display the menu
        displayMenu(action);
        // add a node
        if (action == 1) {
            getUserInput("Enter a number", data);
            tree.insert(data);
        } else if (action == 2) {
            // check if we have a three
            if (tree.isEmpty()) {
                cout << "The tree is empty, first add a node." << endl;
            } else {
                // first get the value to search for
                getUserInput("Enter a number to find", data);
                // now search for the value
                if (tree.search(data)){
                    cout << data << " was found in the binary tree" << endl;
                } else {
                    cout << data << " was not found in the binary tree" << endl;
                }
            }
        } else {
            break;       // just to remove endless loop warning (should never happen)
        }
        cout << endl;
    }

    return 0;
}
