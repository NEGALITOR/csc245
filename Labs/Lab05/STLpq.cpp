#include <iostream>
#include <queue>

using namespace std;

void printQueue(priority_queue<string> pq);

int main()
{
  priority_queue<string> pq;
  
  pq.push("Jeff");
  pq.push("Bob");
  pq.push("Tim");
  pq.push("Tommy");
  pq.push("Kevin");
  pq.push("Jack");
  pq.push("Faith");
  pq.push("Arianna");
  pq.push("Zade");
  pq.push("Sal");
  
  printQueue(pq);
  
  return 0;
}

void printQueue(priority_queue<string> pq)
{
  priority_queue<string> temp = pq;
  
  while(temp.size() != 0)
  {
    cout << temp.top() << " ";
    temp.pop();
  }
  cout << endl;
  
}