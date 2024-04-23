#include <iostream>
#include <limits>
#include "heapqueue.hpp"
#include "taskBTS.hpp"
#include <string>

using namespace std;
class TaskNode {
public:
    int priority;
    int minutes;
    string dueDate;
    string task;

    // Constructor
    TaskNode(int m, string t, int day, int month, string due_date) : priority(day + month * 31), minutes(m), task(t), dueDate(due_date) {}

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

void insert_task(HeapQueue<TaskNode *, TaskNode::Compare>& pqf, TaskBST<TaskNode*>& bstTree) {
  int date[3];
  int minutes;
  char delimiter = '/';
  string task;
  cout << "Insert a task you would like to work on: " << endl;
  getline(cin, task);
  cout << "When is it due? " << endl;
  cout << "day: " << endl;
  cin >> date [1];
  cout << "month: " << endl;
  cin >> date[0];
  cout << "year: " <<endl;
  cin >> date[2];
  string due_date = to_string(date[2]) + "-" + to_string(date[0]) + "-" + to_string(date[1]); 
  cout << "How many minutes will it take? (Enter a whole number): " << endl;
  cin >> minutes;

  std::cin.ignore(numeric_limits<streamsize>::max(), '\n');


  TaskNode *node = new TaskNode( minutes, task, date[0], date[1], due_date);
  pqf.insert(node);
  bstTree.insert(minutes, task, date[0], date[1], due_date);
}

int main() {
  
  HeapQueue<TaskNode *, TaskNode::Compare> pq;
  TaskBST<TaskNode*> bstTree;

  // CREATING A TODO LIST:
  // prompt the use for number of tasks n
  // create a list of integers from 1 to the n
  // ask the user for the task
  // ask the user for the priority of the task ranging from 1 to 10 from 1 being the highest and 10 being the lowest
  // add the task node to the priority queue pq
  // remove the number from the list of integers
  // repeat until the list of integers is empty
  bool new_task = true;
  bool terminate_program = false;
  
  
  int n;
  

  // std::cin.ignore(numeric_limits<streamsize>::max(), '\n'); //mixing cin and getline is disastrous, this is needed to clear the /n and let getline read sth

  // for (int i = 0; i < n; i++){
  //   int priority;
  //   int minutes;
  //   string task;
  //   string description;

  //   cout << "Enter the task: " << endl;
  //   getline(cin, task);

  //   cout << "Describe the task: " << endl;
  //   getline(cin,description);

  //   cout << "On a scale from 1-10 with 1 being the highest, What is the priority of this task: (Enter a whole number)" << endl;
  //   cin >> priority;

  //   cout << "How many minutes will it take? (Enter a whole number): " << endl;
  //   cin >> minutes;

  //   std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
  //   TaskNode *node = new TaskNode(priority, minutes, task, description);
  //   pq.insert(node);
  // }
  
while ((!pq.empty() || new_task == true) && terminate_program == false) {
  if (new_task == true){
    insert_task(pq,bstTree);
  }
  else{
    cout << "Your next priority is: " << pq.min()->task << endl;
    cout << "You have: " << pq.min() -> minutes << " minutes left on this task" << endl;
    cout << "When you are done with the task, yes to complete the task or no if you wanna stop working on it? (Enter y for yes and n for no) ";
    string status;
    cin >> status;
    string i;
    if (status == "y"){
      pq.removeMin();

      if (pq.empty()){
        cout << "You are done with all your tasks! Would you like to insert a new task or are you done for the day? (y for new task, n for done)" << endl;

        cin >> status;

        if (status == "n"){
          terminate_program = true;
          break;
        }
      }
      else{
        HeapQueue<TaskNode *, TaskNode::Compare> toPrint = pq;
        while (!toPrint.empty()){
          cout << toPrint.min()->task << endl;
          toPrint.removeMin();
        }
      }
      
    }
    else {
      int minutes_worked;
      cout << "How many minutes did you work on that task? " << endl;
      cin >> minutes_worked;
      int *x = &pq.min() -> minutes;
      *x = *x  - minutes_worked;
      // cout << "Did you start working on your most important task? (Enter y for yes and n for no) " << endl;
      // string start;
      // int MinutesWorked;
      // string i;
      // cin >> start;
      cout << "You need to work on " << pq.min()->task << " for " << pq.min()->minutes << "minutes to finish this task" << endl;
    }
    }


  string decision;
  cout << "Would you like to add a new task or work on your current tasks? ('a' for add new task and 'w' to work on tasks)" << endl;
  cin >> decision;
  std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
  new_task = true ? decision == "a" : false;
  
}
  
}