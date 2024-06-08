#include <iostream>
using namespace std;

double temp;

double convert(double value); //function prototype

int main()
{
  //Main program goes here

  cout << "Give temperature in Celsius: ";
  cin >> temp;
  
  cout << temp << " degrees Celsius is "<< convert(temp) << " degrees Fahrenheit." << endl;
  
  return 0;
}

double convert(double tmp)
{
  return 1.8 * tmp + 32.0;
}