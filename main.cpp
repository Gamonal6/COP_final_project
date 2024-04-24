#include <iostream>
#include <limits>
#include "heapqueue.hpp"
#include "taskBTS.hpp"
#include <string>
#include <chrono>
using namespace std::chrono;
using namespace std;
class TaskNode {
public:
    string printDate;
    int priority;
    int percentage;
    int dueDate;
    string task;
    TaskNode* left = nullptr;
    TaskNode* right = nullptr;

    // Constructor
    TaskNode(int m, string t, int due_date, int priority, string print_date) : priority(priority), percentage(m), task(t), dueDate(due_date), printDate(print_date) {}

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

int TaskNode::SubtractMinutes::operator()(TaskNode *node, int percentage) {
  node->percentage -= percentage;
  return node->percentage;
}


bool TaskNode::Compare::operator()(const TaskNode &n1,
                                      const TaskNode &n2) const {

  return lessThan ? n1.priority < n2.priority : n1.priority > n2.priority;
}

bool TaskNode::Compare::operator()(const TaskNode *n1,
                                      const TaskNode *n2) const { //What if tasks have equal priority
  return lessThan ? n1->priority > n2->priority
                  : n1->priority < n2->priority;
}

void delete_task(HeapQueue<TaskNode *, TaskNode::Compare>& pqf, TaskBST<TaskNode*>& bstTree) {

  bstTree.deleteNode(pqf.min()->dueDate);
  pqf.removeMin();

}

void insert_task(HeapQueue<TaskNode *, TaskNode::Compare>& pqf, TaskBST<TaskNode*>& bstTree) {
  int date[3];
  int percentage = 100;
  char delimiter = '-';
  int priority;

  string task;
  cout << "Insert a task you would like to work on: " << endl;
  getline(cin, task);
  cout << "When is it due (YYYY-MM-DD)? " << endl;
  cin >> date[0] >> delimiter >> date[1] >> date[2];
  int due_date = (date[0] * 12*31)+ (date[1]*31) + date[2];
  string print_date = to_string(date[0]) + "-" + to_string(date[1]) + "-" + to_string(date[2]);
  cout << "From a scale of 0-100, what is the priority of this task?" << endl;
  cin >> priority;
  while (priority < 0 || priority > 100){
    cout << "Please enter a priority between 0 and 100: " << endl;
    cin >> priority;
  }

  std::cin.ignore(numeric_limits<streamsize>::max(), '\n');


  TaskNode *node = new TaskNode( percentage, task, due_date, priority, print_date);
  pqf.insert(node);
  bstTree.insert(node);
}

int main() {

  HeapQueue<TaskNode *, TaskNode::Compare> pq;
  TaskBST<TaskNode*> bstTree;

  bool new_task = true;
  bool terminate_program = false;


  int n;

while ((!pq.empty() || new_task == true) && terminate_program == false) {
  if (new_task == true){
    insert_task(pq,bstTree);
  }
  else{
    cout << "Your next priority is: " << pq.min()->task << endl;
    cout << "You have " << pq.min()->percentage << " % of work left of this task" << endl;
    cout << "If you are 100% done with the task, enter y to indicate that its finished or n if you haven't finished it yet. ";
    string status;
    cin >> status;
    while(status != "y" && status != "n"){
      cout << "Invalid input, enter y or n: ";
      cin >> status;
    }
    if (status == "y"){
      delete_task(pq, bstTree);
      bstTree.displayTasks();

      if (pq.empty()){
        cout << "You are done with all your tasks! Would you like to insert a new task or are you done for the day? (y for new task, n for done)" << endl;

      
        cin >> status;
        while(status != "y" && status != "n"){
          cout << "Invalid input, enter y or n: ";
          cin >> status;
        }

        if (status == "n"){
          terminate_program = true;
          break;
        }
        else if(status == "y"){
            insert_task(pq,bstTree);
        }
      }

    }
    else {
      int percent_done;
      cout << "How much percent of the task did you finish (enter a number from 0 - 100? " << endl;
      cin >> percent_done;
      while (percent_done < 0 || percent_done > 100){
        cout << "Invalid input, enter a number from 0 - 100: " << endl;
        cin >> percent_done;
      }
      int *x = &pq.min() -> percentage;
      *x = *x  - percent_done;
      cout << "You still have " << pq.min()->percentage << "% work left for task " << pq.min()->task << endl;
    }
    }


  string decision;
  cout << "Would you like to add a new task or work on your current tasks? ('a' for add new task and 'w' to work on tasks)" << endl;
  cin >> decision;
  std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
  new_task = true ? decision == "a" : false;

}

}