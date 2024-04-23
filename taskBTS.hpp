#ifndef TASKBST_H
#define TASKBST_H

#include <iostream>
using namespace std;
template <typename T>
class TaskBST {
private:
    T root; 

    T insert(T node, int m, const std::string& title, int day, int month,const std::string& date) {
        if (!node) {
            return new T(m, title, day, month, date); 
        }
        if (date < node->dueDate) {
            node->left = insert(node->left, date, title);
        } else {
            node->right = insert(node->right, date, title);
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
    void insert(int m, const std::string& title, int day, int month, const std::string& date) {
        root = insert(root, m, title, day, month, date);
    }

    void displayTasks() {
        inorderTraversal(root);
    }
};

#endif