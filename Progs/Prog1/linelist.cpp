#include <iostream>
#include "linelist.h"

LineList::LineList()
{
    LineNode* line = new LineNode;
    LineNode* line2 = new LineNode;

    line->info = topMessage;
    currLine = line;
    currLineNum = 0;
    length = 0;
    line2->info = bottomMessage;
    currLine->back = NULL;
    currLine->next = line2;
    line2->back = line;
    line2->next = NULL;
}

void LineList::goToTop()
{
    // Post : Advances currLine to line 1
    currLineNum = 1;
    while (currLine->back != NULL)
        currLine = currLine->back;

}

void LineList::goToBottom()
{
    // Post : Advances currLine to last line

    currLineNum = length;
    while (currLine->next != NULL)
        currLine = currLine->next;

}

void LineList::insertLine(string newLine)
{
    // post : newLine has been inserted after the current line

    LineNode* line = new LineNode;

    line->info = newLine;
    line->back = currLine;
    line->next = currLine->next;

    currLine->next->back = line;
    currLine->next = line;
    currLine = line;

    //cout << currLineNum << endl;

    currLineNum++;
    length++;

    //cout << currLineNum << endl;
}

void LineList::deleteLine()
{
    // post : deletes the current line leaving currentLine
    //	  pointing to line following

    if (currLine->info != bottomMessage && length > 0)
    {
                    
      if (currLineNum > 1)
      {
          LineNode* line = new LineNode;
          line = currLine;

          currLine->next->back = line->back;
          currLine->back->next = line->next;
          currLine = line->back;

          currLineNum--;
          length--;

      }
      else if (currLineNum == 1)
      {
          //currLine->next = currLine;
          //currLine->back = currLine;                                                

          LineNode* line = new LineNode;
          line = currLine;

          //cout << line << endl;
                                  
          currLine->next->back = line->back;
          currLine->back->next = line->next;
          currLine = line->back;

          if (length == 1)
          {
              currLineNum = 0;
          }
          else
          {
              currLineNum--;
                                                             
          }
          
          length--; 
          
      }
      
      //cout << length << endl;
      //cout << currLineNum << endl;

    }

}

void LineList::printList()
{
    int tempNum = currLineNum;
    LineNode* line = new LineNode;
    line = currLine;
  
    goToTop();
    for (currLineNum; currLineNum <= length; currLineNum++)
    {
        cout << currLineNum << "> " << currLine->next->info << endl;
        currLine = currLine->next;
  
    }
  
    currLine = line;
    currLineNum = tempNum;

}

string LineList::getCurrLine() const
{
    return currLine->info;

}

void LineList::moveNextLine()
{
    // Post : Advances currLine (unless already at last line)
    if (currLine->next->info != bottomMessage && currLineNum <= length)
    {
        currLine = currLine->next;
        currLineNum++;
    }

}

void LineList::movePrevLine()
{
    // Post : Advances currLine (unless already at last line)
    if (currLineNum > 0 && length > 0 && currLine->back->info != topMessage)
    {
        currLine = currLine->back;
        currLineNum--;
    }

}

int LineList::getCurrLineNum() const
{
    return currLineNum;

}

int LineList::getLength() const
{
    return length;

}
