#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>  
#include <algorithm>

using namespace std;

#include "BinarySearchTree.h"
#include "HashTable.h"

void run(ofstream &outfile, ifstream &infile);
void menu(string word, HashTable &dict, ofstream &outfile, ifstream &infile);
void readInDict(HashTable &dict);
void checkWord(vector<string> &contents, HashTable &dict, ofstream &outfile, ifstream &infile);
void addToTree(string word);
bool inDict(HashTable &dict, string word);
void swap(string word, HashTable &dict);
void split(vector<string> &contents, string content);



//BNode Struct
struct BNode
{
  string word;
  int lineNum;
  
  bool operator < (BNode otherStruct) const 
  {
    return ( word < otherStruct.word );
  }
  
};

typedef BinarySearchTree<BNode> BST;
ostream & operator << (ostream & out, BNode & temp) 
{
  out << temp.word << " " << temp.lineNum;
  return out;
}


typedef BinarySearchTree<BNode> BST;

BNode bN = {"",0};
BST bst(bN);
HashTable ignoredWords(1000);
int lineNumber = 1;


//Main
int main(int argc, char *argv[])
{
  //Checks Argument
  if (argc < 2)
  {
    cout << "No Filename Given -- Program Exiting" << endl;
    return 0;
  }
  
  ifstream inFile(argv[1]);
  ofstream outFile;
  
  run(outFile, inFile);
  
  return 0;
}

void run(ofstream &outfile, ifstream &infile)
{
  outfile.open("dict.txt", ofstream::app);
  
  string fileContent = "";
  vector<string> contentCheck;
  HashTable dict(1000);
  readInDict(dict);
  
  getline(infile, fileContent);
  
  while(infile)
  {
    split(contentCheck, fileContent);
    checkWord(contentCheck, dict, outfile, infile);
    getline(infile, fileContent);
    lineNumber++;
    
  }
  
  infile.close();
  outfile.close();
  
  outfile.open("notfound.txt");
  bst.printTree(outfile);
  outfile.close();
  
  cout << "\n***  All Spell Checking Has Now Been Completed ***\n\nNow Exiting..." << endl;
  
}


//Displays the Menu and awaits for input in order to execute accordingly
void menu(string word, HashTable &dict, ofstream &outfile, ifstream &infile)
{
  cout << "\033[2J\033[1;1H";
  cout << "!@#$%^&*(){}\tTHE SPELL CHECKER PROGRAM\t!@#$%^&*(){}\n" << endl;
  
  cout << word << " On Line " << lineNumber << " Was Not Found in the Dictionary\n" << endl;
  
  cout << "A)\tAdd the Word to Dictionary\n"
        "I)\tIgnore Word, and Skip Future References\n"
        "G)\tGo On to Next Word\n"
        "S)\tSearch For A Suggested Spelling\n"
        "Q)\tQuit Spell Checking File\n\n";
  
  cout << "Selection : ";
  
  char input[0];
  //cin.ignore();
  cin >> input;
  input[0] = tolower(input[0]);
  cin.ignore();    
  //cout << endl;
  
  switch(input[0])
  {
      //Adds word to dictionary
      case 'a':
        dict.insert(word);
        outfile << word << endl;
        cout << "\nThe Word " << word << " Has Been Successfully Inserted" << endl;
        cout << "Press Enter to Continue...";
        cin.ignore();
        break;
      
      //Adds to ignored words list
      case 'i':
        ignoredWords.insert(word);        
        break;
      
      //Go to next word
      case 'g':
        break;
      
      //Suggests a word
      case 's':
        swap(word, dict);
        cin.ignore();
        menu(word, dict, outfile, infile);
        break;
      
      //Quit
      case 'q':
        cout << "Now Exiting..." << endl;
        
        infile.close();
        outfile.close();
        
        outfile.open("notfound.txt");
        bst.printTree(outfile);
        outfile.close();
        
        exit(1);
        break;
      
      //Invalid Input
      default:
        cout << "\nSelection Error! Please Press Enter to Try Again...";
        cin.ignore();
        menu(word, dict, outfile, infile);
        break;
      
  }
  
}



//Reads the dict.txt into a HashTable
void readInDict(HashTable &dict)
{
  ifstream inFile;
  
  inFile.open("dict.txt");
  string content = "";
  
  getline(inFile, content);
  
  while (inFile)
  {
    dict.insert(content);
    getline(inFile, content);
    
  }
  
  inFile.close();
}



//Checks if the content is a word or not
void checkWord(vector<string> &contents, HashTable &dict, ofstream &outfile, ifstream &infile)
{
  
  string temp = "";
  bool isWord = false;
  char firstChar, lastChar;
  
  //cout << contents.size();
  
  for (int i = 0; i < contents.size(); i++)
  {
    temp = contents[i];
    //cout << "Line: " << lineNumber << "\tContent: \t\t" << contents[i] << endl;
    
    if (temp.length() >= 1)
    {
      firstChar = temp.at(0);
      lastChar = temp.at(temp.length() - 1);
      
      if (isalpha(firstChar))
      {
        isWord = true;
        
        //cout << "Is a Word: \t\t";
        
        if (isalpha(lastChar))
        {
          isWord = true;
          
        }
        else
        {
          temp = temp.substr(0, temp.length() - 1);
          isWord = true;
          //cout << "New Word:\t" << temp << "\t";
          
        }
      }
      else if (isalpha(lastChar))
      {
        temp = temp.substr(0, temp.length() - 1);
        isWord = true;
        //cout << "New Word:\t" << temp << "\t";
      }
      
      if (!isWord)
      {
        //cout << "Is Not a Word" << endl;
      }
      else
      {
        for(int i = 0; i < temp.length(); i++)
        {
          temp[i] = tolower(temp[i]);
        }
        
        if (inDict(dict, temp))
        {
          //cout << "Found in the Dictionary" << endl;
          
        }
        else
        {
          //cout << "Could not Find in Dictionary" << endl;
          addToTree(temp);
          menu(temp, dict, outfile, infile);
        }
      }
      
      isWord = false;
      
    }
    else
    {
      cout << "Not a Word" << endl;
    
    }
  }
}



//Adds non-dictionary items to a BST
void addToTree(string word)
{
  BNode BN = {word, lineNumber};
  bst.insert(BN);
}


//Checks if word is in the Dictionary
bool inDict(HashTable &dict, string word)
{
  if (dict.find(word) || ignoredWords.find(word))
    return true;
  else
    return false;
  
}


//Swaps the word around in order to suggest a word
void swap(string word, HashTable &dict)
{
  string temp = word;
  string c;
  int i;
  bool found = false;
  
  for (i = 0; i < word.length() - 1; i++)
  {
    c = word.at(i);
    temp.erase(i,1);
    
    //cout << temp << endl;
    
    temp.insert(i + 1, c);
    
    //cout << temp << endl;
    
    if(inDict(dict, temp))
    {
      cout << "Suggested Spelling : " << temp << endl << endl;
      i = word.length();
      found = true;
    }
    
    temp = word;
    
  }
  
  if(!found)
    cout << "No Correct Spelling Was Found...\n" << endl;
  
  cout << "Press Enter to Return to Menu..." << endl;
  
}

//Splits the sentence into seperate words
void split(vector<string> &contents, string content)
{
  char *ptr = new char [content.length()+1];
  strcpy(ptr, content.c_str());
  
  ptr = strtok(ptr, " ");
  
  while (ptr != NULL)  
  {  
      //cout << ptr << endl;
      contents.push_back(ptr);
      ptr = strtok(NULL, " ");
  }
  
}





