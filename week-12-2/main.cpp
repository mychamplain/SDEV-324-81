/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Champlain College SDEV-345-81
 *
 * C++ Week 12: Red Black Binary Trees (first semester) - (2020/11/27)
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Given an initially empty red black tree,  write code to insert the following keys (30,28,21,11,17,4).
 * Include your source code, output and a color-coded diagram of the tree.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Written by Llewellyn van der Merwe <llewellyn.vandermerw@mymail.champlain.edu>, November 2020
 * Copyright (C) 2020. All Rights Reserved
 * License GNU/GPL Version 2 or later - http://www.gnu.org/licenses/gpl-2.0.html
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/** Taken from geeksforgeeks
    https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/
    Adapted by Llewellyn van der Merwe **/

 /** C++ implementation for
   Red-Black Tree Insertion 
   This code is adopted from  
   the code provided by 
   Dinesh Khandelwal in comments **/

#include <bits/stdc++.h>

using namespace std;

enum Color {
    RED, BLACK
};

struct Node {
    int data;
    bool color;
    Node *left, *right, *parent;

    // Constructor
    Node(int data) {
        this->data = data;
        left = right = parent = nullptr;
        this->color = RED;
    }
};

// Class to represent Red-Black Tree
class RBTree {
private:
    Node *root;
protected:
    void rotateLeft(Node *&, Node *&);

    void rotateRight(Node *&, Node *&);

    void fixViolation(Node *&, Node *&);

public:
    // Constructor
    RBTree() { root = nullptr; }

    void insert(const int &n);

    void inorder();

    void levelOrder();

    void display();
};

// color printing helper
string printColorHelper(Node *root) {
    // check the color
    if (RED == root->color) {
        // red background with white number
        return "\033[1;41;37m " + to_string(root->data) + " \033[0m";
    } else {
        // black background with white number
        return "\033[1;40;37m " + to_string(root->data) + " \033[0m";
    }
}

// A recursive function to do inorder traversal 
void inorderHelper(Node *root) {
    if (root == nullptr)
        return;

    inorderHelper(root->left);
    cout << printColorHelper(root) << "  ";
    inorderHelper(root->right);
}

// display the tree
// Adapted from https://stackoverflow.com/a/51730733/1429677
void displayHelper(const std::string &prefix, Node *node, bool isLeft) {
    if (node != nullptr) {
        // print the prefix
        cout << prefix;
        cout << (isLeft ? "├──" : "└──");
        // print the value of the node
        cout << printColorHelper(node) << endl;
        // enter the next tree level - left and right branch
        displayHelper(prefix + (isLeft ? "│   " : "    "), node->left, true);
        displayHelper(prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

/* A utility function to insert
    a new node with given key
   in BST */
Node *BSTInsert(Node *root, Node *pt) {
    /* If the tree is empty, return a new node */
    if (root == NULL)
        return pt;

    /* Otherwise, recur down the tree */
    if (pt->data < root->data) {
        root->left = BSTInsert(root->left, pt);
        root->left->parent = root;
    } else if (pt->data > root->data) {
        root->right = BSTInsert(root->right, pt);
        root->right->parent = root;
    }

    /* return the (unchanged) node pointer */
    return root;
}

// Utility function to do level order traversal 
void levelOrderHelper(Node *root) {
    if (root == NULL)
        return;

    std::queue<Node *> q;
    q.push(root);

    while (!q.empty()) {
        Node *temp = q.front();
        cout << printColorHelper(temp) << "  ";
        q.pop();

        if (temp->left != NULL)
            q.push(temp->left);

        if (temp->right != NULL)
            q.push(temp->right);
    }
}

void RBTree::rotateLeft(Node *&root, Node *&pt) {
    Node *pt_right = pt->right;

    pt->right = pt_right->left;

    if (pt->right != NULL)
        pt->right->parent = pt;

    pt_right->parent = pt->parent;

    if (pt->parent == NULL)
        root = pt_right;

    else if (pt == pt->parent->left)
        pt->parent->left = pt_right;

    else
        pt->parent->right = pt_right;

    pt_right->left = pt;
    pt->parent = pt_right;
}

void RBTree::rotateRight(Node *&root, Node *&pt) {
    Node *pt_left = pt->left;

    pt->left = pt_left->right;

    if (pt->left != NULL)
        pt->left->parent = pt;

    pt_left->parent = pt->parent;

    if (pt->parent == NULL)
        root = pt_left;

    else if (pt == pt->parent->left)
        pt->parent->left = pt_left;

    else
        pt->parent->right = pt_left;

    pt_left->right = pt;
    pt->parent = pt_left;
}

// This function fixes violations
// caused by BST insertion
void RBTree::fixViolation(Node *&root, Node *&pt) {
    Node *parent_pt = NULL;
    Node *grand_parent_pt = NULL;

    while ((pt != root) && (pt->color != BLACK) &&
           (pt->parent->color == RED)) {

        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;

        /*  Case : A
            Parent of pt is left child
            of Grand-parent of pt */
        if (parent_pt == grand_parent_pt->left) {

            Node *uncle_pt = grand_parent_pt->right;

            /* Case : 1
               The uncle of pt is also red
               Only Recoloring required */
            if (uncle_pt != NULL && uncle_pt->color == RED) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            } else {
                /* Case : 2
                   pt is right child of its parent
                   Left-rotation required */
                if (pt == parent_pt->right) {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                /* Case : 3
                   pt is left child of its parent
                   Right-rotation required */
                rotateRight(root, grand_parent_pt);
                swap(parent_pt->color,
                     grand_parent_pt->color);
                pt = parent_pt;
            }
        }

            /* Case : B
               Parent of pt is right child
               of Grand-parent of pt */
        else {
            Node *uncle_pt = grand_parent_pt->left;

            /*  Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if ((uncle_pt != NULL) && (uncle_pt->color == RED)) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            } else {
                /* Case : 2
                   pt is left child of its parent
                   Right-rotation required */
                if (pt == parent_pt->left) {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                /* Case : 3
                   pt is right child of its parent
                   Left-rotation required */
                rotateLeft(root, grand_parent_pt);
                swap(parent_pt->color,
                     grand_parent_pt->color);
                pt = parent_pt;
            }
        }
    }

    root->color = BLACK;
}

// Function to insert a new node with given data
void RBTree::insert(const int &data) {
    Node *pt = new Node(data);
    // Do a normal BST insert
    root = BSTInsert(root, pt);

    // fix Red Black Tree violations
    fixViolation(root, pt);
}

// Function to do inorder and level order traversals
void RBTree::inorder() { inorderHelper(root); }

void RBTree::levelOrder() { levelOrderHelper(root); }

// display the binary tree
void RBTree::display() { displayHelper("", root, false); }

// Driver Code 
int main() {
    // empty tree
    RBTree tree;

    // lets load the values
    tree.insert(30);
    tree.insert(28);
    tree.insert(21);
    tree.insert(11);
    tree.insert(17);
    tree.insert(4);

    cout << endl;
    // show the color code
    cout << "Color Code" << endl;
    cout << "\033[1;40;37m BLACK \033[0m" << endl;
    cout << "\033[1;41;37m RED   \033[0m" << endl;
    cout << endl;
    // show inorder traversal
    cout << "Inoder Traversal of Created Tree" << endl;
    tree.inorder();
    cout << endl;
    cout << endl;
    // show level order traversal
    cout << "Level Order Traversal of Created Tree" << endl;
    tree.levelOrder();
    cout << endl;
    cout << endl;
    // show the tree
    cout << "Display Tree" << endl;
    tree.display();
    cout << endl;
    return 0;
}
