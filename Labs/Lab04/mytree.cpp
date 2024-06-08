#include <iostream>
#include <cstdlib>
#include "bst.h"

using namespace std;

int main()
{
	BinarySearchTree<int> T(0);
  BinarySearchTree<int> E(0);
  
  T.insert(6);
  T.insert(2);
  T.insert(1);
  T.insert(4);
  T.insert(3);
  T.insert(8);
  
  cout << "InOrder is: "; T.printTree();
  cout << "\nPostOrder is: "; T.postOrder();
  cout << "\n\nHeight is: " << T.Height() << endl;
  cout << "Num of Leaves: " << T.numLeaves() << endl << endl;
  
  if(T.isBalanced())
    cout << "It's Balanced!" << endl;
  else
    cout << "It's NOT Balanced!" << endl;
  
  cout << "\nInserted a 9. " << endl;
  T.insert(9);
  
  if(T.isBalanced())
    cout << "It's Balanced!" << endl;
  else
    cout << "It's NOT Balanced!" << endl;  
}