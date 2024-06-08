#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

void Initialize(vector<int> &vec)
{
  cout << "Enter 5 Integers: " << endl;
  
  for(int i = 0; i < 5; i++)
  {
    int temp;
    cin >> temp;
    vec.push_back(temp);
  }
}

void Print(vector<int> vec)
{
  cout << "Values in the vector are: "<< endl;
  
  for(int i=0; i < vec.size(); i++)
  {
    cout << vec[i] << " ";
  }
  cout << endl;
  
}


void Reverse(vector<int> &vec)
{
  reverse(vec.begin(), vec.end());
}


int main()
{
  stack<string> s1, s2;
  
  s1.push("Hi there");
  s1.push("IDK");
  
  s2.push("Hi there Two");
  s2.push("IDK Two");
  
  if (s1 == s2)
  {
    cout << "Stacks are the same" << endl;
  }
  else if (s1 < s2)
  {
    cout << "Stack 1 is less than Stack 2" << endl;
  }
  else if (s1 > s2)
  {
    cout << "Stack 1 is greater than Stack 2" << endl;
  }
  
  vector<int> v;
  
  Initialize(v);
  Print(v);
  
  Reverse(v);
  Print(v);
  
  sort(v.begin(), v.end());
  Print(v);
  
  return 0;
}






