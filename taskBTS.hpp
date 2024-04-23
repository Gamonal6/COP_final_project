#ifndef TASKBST_H
#define TASKBST_H

#include <iostream>
using namespace std;
template <typename T>
class TaskBST {
private:
    T root; 

    T insert(T node, T new_node) {
        if (!node) {
            return new_node; 
        }
        if (new_node->dueDate < node->dueDate) {
            node->left = insert(node->left, new_node);
        } else {
            node->right = insert(node->right, new_node);
        }
        return node;
    }

    void inorderTraversal(T node) {
        if (node) {
            inorderTraversal(node->left);
            std::cout << "Due Date: " << node->dueDate << ", Title: " << node->task << std::endl;
            inorderTraversal(node->right);
        }
    }

public:
    TaskBST() : root(nullptr) {}
    void insert(T new_node) {
        root = insert(root, new_node);
    }

    void displayTasks() {
        inorderTraversal(root);
    }
};

#endif