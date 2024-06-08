#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int maxElemLength(const vector<int>& v);
int GetDigit(int number, int k);
vector<queue<int> > ItemsToQueues(const vector<int>& L, int k);
vector<int> QueuesToArray(vector< queue<int> >& QA, int numVals);
void RadixSort(vector<int>& L, int numDigits);
void PrintVector(const vector<int>& L);

//Main
int main()
{
	int a[] = {380, 95, 345, 382, 260, 100, 492};
	vector<int> L(a, a+7);
  
  cout << "Before: ";
  PrintVector(L);
	
  RadixSort(L, maxElemLength(L));
  
 	cout << "After: ";
	PrintVector(L);
}

//Finds the maximum length element within the list
int maxElemLength(const vector<int>& v)
{
	int maxLen(0);

  for(int i = 0; i < v.size(); ++i)
		maxLen = max(maxLen, (int)log10(v[i]) + 1);

	return maxLen;

}

//Gets the digit
int GetDigit(int number, int k)
{
	int maxK = log10(number);

	if(k > maxK)
		return 0;
	else
		return (int)(number/pow(10, k))%10;

}

//Puts the items into a queue
vector<queue<int> > ItemsToQueues(const vector<int>& L, int k)
{
	vector<queue<int> > q(10);

	for(int i = 0; i < L.size(); ++i)
	{
		int pos = GetDigit(L[i], k);
		q[pos].push(L[i]);
   
	}

	return q;

}

//Puts the Queues in the Vector of queues indexed 0 - 9
vector<int> QueuesToArray(vector< queue<int> >& QA, int numVals)
{
	vector<int> v;

	for(int i = 0; i < QA.size(); ++i)
	{
		while(!QA[i].empty())
		{
			v.push_back(QA[i].front());
			QA[i].pop();
      
		}
   
	}

	return v;

}

//Performs Radix Sort by utilizing a queue and array for bucket sorting
void RadixSort(vector<int>& L, int numDigits)
{
	vector<queue<int > > QA(10);

	for(int i = 0; i < numDigits; ++i)
	{
		QA = ItemsToQueues(L, i);
		L = QueuesToArray(QA, L.size());

	}

}

//Prints L
void PrintVector(const vector<int>& L)
{

	for(int i = 0; i < L.size(); ++i)
		cout << L[i] << " ";

	cout << endl;

}

