#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "linelist.h"

using namespace std;

void readFile(LineList &list, string line, char *argv[]);
void setFile(LineList &list, char *argv[]);
void readInput(LineList &list, string line);

//Main function which executes the functions from editor.cpp
int main(int argc, char *argv[])
{
  //if no argument is in putted
  if (argc == 1)
  {
    cout << "Error -- No Filename Entered!" << endl;
    exit(1);
  }
  //if argument is inputted
  else if (argc == 2)
  {
    LineList L;
    string line;
    
    readFile(L, line, argv);
    
    //cout << L.getCurrLineNum() << endl;
    //cout << L.getLength() << endl;
    
    readInput(L, line);
    setFile(L, argv);
    
  }
    
  return 0;
}

//Reads the file into the LineList
void readFile(LineList &list, string line, char *argv[])
{
  //int call = 0;
  ifstream file(argv[1]);
  
  //checks if file exists in current directory
  if(file)
  {
    //until the file ends
    while(file)
    {
      getline(file, line);
      if (file.eof())
        break;
      list.insertLine(line);
      
      //call++;
      //cout << call << " calls" << endl;
      //cout << list.getCurrLineNum() << endl;
      //cout << list.getLength() << endl;
        
    }
    cout << "\nL or l to display lines\nP or p to go to previous line\nN or n to go to next line\nI or i to insert line\nD or d to delete line\nH or h to display this help message again\n" << endl;
  }
  else
  {
    cout << "Error -- File Does Not Exist in Current Directory" << endl;
    exit(1);
  }
  
  
}

//Overwrites the file with the changes that the client has made
void setFile(LineList &list, char *argv[])
{
  ofstream file;
  file.open(argv[1]);
  list.goToTop();
  
  //cout << list.getCurrLineNum() << endl;
  
   
  //scans user changes and overwrites text file by traversing line by line
  for (int i = list.getCurrLineNum(); i <= list.getLength(); i++) 
  {
    //cout << i << endl;
    list.moveNextLine();
    file << list.getCurrLine() << endl;
    //cout << list.getCurrLine() << endl;
    
  }
  
  file.close();
  
}

//Reads client input to determine what functions from linelist.cpp to execute
void readInput(LineList &list, string line)
{
  list.printList();
  
  char input = ' ';
  
  //e is used to exit the while loop
  while (tolower(input) != 'e')
  {
    cout << list.getCurrLineNum() << "> ";
    cin >> input;
    
    //determine and match the cases based on input
    switch (tolower(input))
    {
      case 'i':
        cout << list.getCurrLineNum() + 1 << "> ";
        cin.ignore();
        getline(cin, line);
        list.insertLine(line);
        break;
      
      case 'd':
        list.deleteLine();
        break;
      
      case 'l':
        cout << endl;
        list.printList();
        break;
      
      case 'p':
        list.movePrevLine();
        break;
      
      case 'n':
        list.moveNextLine();
        break;
      
      case 'h':
        cout << "\nL or l to display lines\nP or p to go to previous line\nN or n to go to next line\nI or i to insert line\nD or d to delete line\nH or h to display this help message again\n" << endl;
        break;
        
    }
  }

}

