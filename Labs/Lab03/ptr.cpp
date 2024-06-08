#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

struct RecType
{
  int age;
  float weight;
  char gender;
};

int main()
{
  int num = 5;
  int *intPtr = NULL;
  intPtr = &num;
  *intPtr *= 10;
  cout << "*intPtr Points To: " << *intPtr << endl;
  
  RecType *recPtr;
  recPtr = new RecType;
  
  recPtr->age = 25;
  recPtr->weight = 190;
  recPtr->gender = 'M';
  
  recPtr->age += 5;
  
  cout << "Three Fields Pointed to By recPtr : " << recPtr->age << " " << recPtr->weight << " " << recPtr->gender << endl;
  
  delete recPtr;
  recPtr = NULL;
  
  char *strPtr = new char[50];
  strcpy(strPtr, "Operating Systems");
  cout << "strPtr points to : " << strPtr << endl;
  
  int count = 0;
  for (int i = 0; i < strlen(strPtr); i++)
  {
    if (islower(*(strPtr + i)))
      count++;
  }
  
  cout << "owerCase Letters Pointed To By strPtr : " << count << endl;
  
  strPtr += 10;
  cout << "Printing strPtr after adding 10 : " << strPtr << endl;
  strPtr -= 10;
  
  delete[] strPtr;

  return 0;
}