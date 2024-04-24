#ifndef TASKBST_H
#define TASKBST_H
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;
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
        } else if(new_node->dueDate > node->dueDate) {
            node->right = insert(node->right, new_node);
        }
      else if(new_node->dueDate == node->dueDate){
        if(new_node->priority < node->priority){
          node->left = insert(node->left, new_node);
        }
        else{
          node->right = insert(node->right, new_node);
        }
      }
        return node;
    }

    void inorderTraversal(T node) {
        if (node) {
            inorderTraversal(node->left);

           
            inorderTraversal(node->right);

             std::cout << "Due Date: " << node -> printDate << "|| Task: " << node->task << " || Priority: " << node->priority << std::endl;
        }
    }

    T deleteNode(T node, int key) {
        if (!node) return nullptr; 

        if (!node->left && !node->right) {
            delete node;  // Node is a leaf
            return nullptr;
        }
        if (key < node->dueDate)
            node->left = deleteNode(node->left, key);
        else if (key > node->dueDate)
            node->right = deleteNode(node->right, key);
        else {
            if (!node->left) {
                T temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                T temp = node->left;
                delete node;
                return temp;
            }


            T temp = minValueNode(node->right);

            node->dueDate = temp->dueDate;

            node->right = deleteNode(node->right, temp->dueDate);
        }
        return node;
    }

    T minValueNode(T node) {
        T current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

public:
    TaskBST() : root(nullptr) {}
    void insert(T new_node) {
        root = insert(root, new_node);
    }

    void displayTasks() {
        inorderTraversal(root);
    }

    void deleteNode(int date){
        root = deleteNode(root, date);

    }

};

#endif