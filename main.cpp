#include <iostream>
#include <limits>
#include "heapqueue.hpp"

using namespace std;

class TaskNode {
public:
    int priority;
    int minutes;
    string task;
    string description;

    // Constructor
    TaskNode(int p, int m, string t, string d) : priority(p), minutes(m), task(t) , description(d){}

class Compare {
public:
  Compare(bool lessThan = true) : lessThan(lessThan) {};
  bool operator()(const TaskNode &n1, const TaskNode &n2) const;
  bool operator()(const TaskNode *n1, const TaskNode *n2) const;
private:
  bool lessThan;
};

class SubtractMinutes {
public:
  int operator()(TaskNode *node, int minutes);
};
    // Destructor (if needed)
    // ~Node() {}
};

int TaskNode::SubtractMinutes::operator()(TaskNode *node, int minutes) {
  node->minutes -= minutes;
  return node->minutes;
}


bool TaskNode::Compare::operator()(const TaskNode &n1,
                                      const TaskNode &n2) const {

  return lessThan ? n1.priority < n2.priority : n1.priority > n2.priority;
}

bool TaskNode::Compare::operator()(const TaskNode *n1,
                                      const TaskNode *n2) const { //What if tasks have equal priority
  return lessThan ? n1->priority < n2->priority
                  : n1->priority > n2->priority;
}

int main() {
  
    HeapQueue<TaskNode *, TaskNode::Compare> pq;

  // CREATING A TODO LIST:
  // prompt the use for number of tasks n
  // create a list of integers from 1 to the n
  // ask the user for the task
  // ask the user for the priority of the task ranging from 1 to 10 from 1 being the highest and 10 being the lowest
  // add the task node to the priority queue pq
  // remove the number from the list of integers
  // repeat until the list of integers is empty

  int n;
  cout << "Enter the number of tasks you would like to do today:" << endl;
  cin >> n;
  std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); //mixing cin and getline is disastrous, this is needed to clear the /n and let getline read sth

  for (int i = 0; i < n; i++){
    int priority;
    int minutes;
    string task;
    string description;

    cout << "Enter the task: " << endl;
    getline(cin, task);

    cout << "Describe the task: " << endl;
    getline(cin,description);

    cout << "On a scale from 1-10 with 1 being the highest, What is the priority of this task: (Enter a whole number)" << endl;
    cin >> priority;

    cout << "How many minutes will it take? (Enter a whole number): " << endl;
    cin >> minutes;

    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
    TaskNode *node = new TaskNode(priority, minutes, task, description);
    pq.insert(node);
  }
  
while (!pq.empty()) {
  cout << "Your next priority is: ";
  cout << pq.min()->task << endl;
  cout << "done with a task? (Enter y for yes and n for no) ";
  string status;
  cin >> status;
  string i;
  if (status == "y"){
    cout << "What task did you complete? (enter the number of the task): ";
    cin >> i;
    int x = stoi(i);
    pq.removeAtIndex(x);
    HeapQueue<TaskNode *, TaskNode::Compare> toPrint = pq;
    while (!toPrint.empty()){
      cout << toPrint.min()->task << endl;
      toPrint.removeMin();
    }
  }
  else
  {
    cout << "Your next priority is: ";
    cout << pq.min()->task << endl;
    cout << "Did you start working on your most important task? (Enter y for yes and n for no) " << endl;
    string start;
    int MinutesWorked;
    string i;
    cin >> start;
    if (start == "n"){
      cout << "You need to " << pq.min()->task << " for " << pq.min()->minutes;
    }
    else
    {
      cout << "What task did you start? (enter the number of the task): ";
      cin >> i;
      int x = stoi(i);
      cout << "How many minutes did you work on the task? " << endl;
      cin >> MinutesWorked;
      pq.PeekAtIndex(x);
      HeapQueue<TaskNode *, TaskNode::SubtractMinutes> toPrint = pq;
    }
    
  }
  

}
  
}