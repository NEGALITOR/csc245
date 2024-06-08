#include <iostream>

#include "BinaryHeap.h"

using namespace std;

int main()
{
  BinaryHeap<char> PQ(50);
  
  for(char letter = 'A'; letter <= 'J'; ++letter)
  {
    PQ.insert(letter);
    
  }
  
  
  PQ.PrintLeaves();
  cout << endl;
  
  //PQ.deleteMin();
  
  cout << "Printing Left Subtree of the Root of Heap: ";
  PQ.printLtSubtree();
  cout << endl;
  /*
  cout << "The Height of Heap Is: " << PQ.Height() << endl;
  
  cout << "The Maximum Value of Heap is: ";
  cout << PQ.findMax() << endl;
  */
  

  return 0;
}