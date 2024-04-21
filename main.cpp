#include <iostream>
#include "heapqueue.hpp"

using namespace std;

class TaskNode {
public:
    int priority;
    string task;

    // Constructor
    TaskNode(int p, string t) : priority(p), task(t) {}

class Compare {
public:
  Compare(bool lessThan = true) : lessThan(lessThan) {};
  bool operator()(const TaskNode &n1, const TaskNode &n2) const;
  bool operator()(const TaskNode *n1, const TaskNode *n2) const;
private:
  bool lessThan;
};

    // Destructor (if needed)
    // ~Node() {}
};

bool TaskNode::Compare::operator()(const TaskNode &n1,
                                      const TaskNode &n2) const {

  return lessThan ? n1.priority < n2.priority : n1.priority > n2.priority;
}

bool TaskNode::Compare::operator()(const TaskNode *n1,
                                      const TaskNode *n2) const {
  return lessThan ? n1->priority < n2->priority
                  : n1->priority > n2->priority;
}

int main() {
  
    HeapQueue<TaskNode *, TaskNode::Compare> pq;

  // CREATING A TODO LIST:
    // prompt the use for number of tasks n
   // create a list of integers from 1 to the n
  // ask the user for the task
   // ask the user for the priority of the task ranging from 1 to n from 1 being the highest and n being the lowest
  // add the task node to the priority queue pq
  // remove the number from the list of integers
  // repeat until the list of integers is empty

  int n;
  cout << "Enter the number of tasks you woudl like to do today? ";
  cin >> n;
  for (int i = 0; i < n; i++){
    int priority;
    string task = "";
    cout << "Enter the task: ";
    cin >> task;
    cout << "what is the priority of this task? ";
    cin >> priority;

    TaskNode *node = new TaskNode(priority, task);
    pq.insert(node);
  }
  
  cout << "Your next priority is: ";
  cout << pq.min()->task << endl;
  cout << "done with a task? ";
  string yes;
  cin >> yes;
  string i;
  if (yes == "y"){
    cout << "What task did you complete? ";
    cin >> i;
    int x = stoi(i);
    pq.removeAtIndex(x);
    HeapQueue<TaskNode *, TaskNode::Compare> toPrint = pq;
    while (!toPrint.empty()){
      cout << toPrint.min()->task << endl;
      toPrint.removeMin();
    }
  }
  
  
}