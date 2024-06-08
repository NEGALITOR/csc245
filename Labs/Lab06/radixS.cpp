#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int maxElemLength(const vector<string>& v);
char GetChar(string s, int k);
vector<queue<string> > ItemsToQueues(const vector<string>& L, int k);
vector<string> QueuesToArray(vector< queue<string> >& QA);
void RadixSort(vector<string>& L, int numDigits);
void PrintVector(const vector<string>& L);
void AddPadding(vector<string>& v, int numChars);
void RemovePadding(vector<string>& v);

//Main
int main()
{
	string a[] = {"zebra", "apple", "orange", "can", "candy", "a", "top", "pumpkin", "today", "parade"};
	vector<string> L(a, a+10);
	
  cout << "Before: ";
  PrintVector(L);
  
	AddPadding(L, maxElemLength(L));
	RadixSort(L, maxElemLength(L));
	RemovePadding(L);
 
	cout << "After: ";
  PrintVector(L);

	return 0;

}

//Finds the maximum length element within the list
int maxElemLength(const vector<string>& v)
{
	int maxLen(0);

	for(int i = 0; i < v.size(); ++i){
		int n = v[i].size();
		maxLen = max(maxLen, n);
	}
	
	return maxLen;
}


//Gets the char
char GetChar(string s, int k)
{
	return s[s.size()-1-k];

}

//Puts the items into a queue
vector<queue<string> > ItemsToQueues(const vector<string>& L, int k)
{
	vector<queue<string> > q(128);

	for(int i = 0; i < L.size(); ++i)
	{
		int pos = (int)GetChar(L[i], k);
		q[pos].push(L[i]);
	}

	return q;
}

//Puts the Queues in the Vector of queues indexed 0 - 9
vector<string> QueuesToArray(vector< queue<string> >& QA)
{
	vector<string> v;

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
void RadixSort(vector<string>& L, int numDigits)
{
	vector<queue<string > > QA(10);

	for(int i = 0; i < numDigits; ++i)
	{
		QA = ItemsToQueues(L, i);
		L = QueuesToArray(QA);

	}

}


//Prints L
void PrintVector(const vector<string>& L)
{
	for(int i = 0; i < L.size(); ++i)
		cout << L[i] << " ";

	cout << endl;

}

//Adds spaces to the end of every word to make it equal length with the longest word in the list
void AddPadding(vector<string>& v, int numChars)
{
	for(int i = 0; i < v.size(); ++i)
	{
		if(v[i].size() < numChars)
		{
			string pad(numChars - v[i].size(), ' ');
			v[i]+=pad;

		}
	}

}

//Removes the spaces that was added with AddPadding
void RemovePadding(vector<string>& v)
{
	for(int i = 0; i < v.size(); ++i)
	{
		for(int j = 0; j < v[i].size(); ++j)
		{
			if(v[i][j] == ' ')
			{
				v[i].erase(j);
				j--;

			}
		}
	}
}