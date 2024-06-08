#include<iostream>
#include<string>
#include <cstdlib>

#include "stack.h"

using namespace std;

void parse(string input, Stack<int>& stack);
void operate(char op, Stack<int>& stack);

bool isOperator(char input);

void printNoPopNew(Stack<int>& stack);
void printPopNoNew(Stack<int>& stack);
void print(Stack<int>& stack);
void clear(Stack<int>& stack);
void duplicate(Stack<int>& stack);
void reverse(Stack<int>& stack);
void negative(Stack<int>& stack);

void add(Stack<int>& stack);
void subtract(Stack<int>& stack);
void multiply(Stack<int>& stack);
void divide(Stack<int>& stack);
void mod(Stack<int>& stack);

int main() //main
{
	Stack<int> finalStack;

	while (cin)
	{
		string input;

		try
		{
			getline(cin, input);
			parse(input, finalStack);
		}
		catch (Underflow e)
		{
			cout << "Illegal Pop -- Stack is Empty." << endl;
		}
		catch (Overflow e)
		{
			cout << "Exception -- Your stack is full!" << endl;
		}



	}

	return 0;
}

//String Parsing Methods
void parse(string input, Stack<int>& stack) //parses through the string
{
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == ' ') //skips spaces
    {
			continue;
    }
    else if(input[i] == '_') //puts a negative sign in front of next value
    {
      int op = 0;
      input[i] = '-';
      op = atoi(input.c_str());
      
      stack.push(op);
      
      i++;
      
		}
    else if (isOperator(input[i])) //checks if operator
		{
			operate(input[i], stack);

		}            
		else if (isdigit(input[i])) //checks if digit
		{
			int op = 0;

			while (i < input.length() && isdigit(input[i]))
			{
				op = (op * 10) + (input[i] - '0');
				i++;
			}

			i--;

			stack.push(op);
		}
    else if (!isdigit(input[i]) && !isOperator(input[i]) && input[i] != '_') //catches if anything else
    {
  		cout << "Exception -- You have entered an invalid expression.  Please re-enter." << endl;
    }
    
    
	}
  
}

void operate(char input, Stack<int>& stack) //switch statement input managament
{
  
	switch (input)
	{    
  	case '+':
  		add(stack);
      break;
  
  	case '-':
  		subtract(stack);
      break;
  
  	case '*':
  		multiply(stack);
      break;
  
  	case '/':
  		divide(stack);
      break;
  
  	case '%':
  		mod(stack);
      break;
  
  	case 'p':
  		printNoPopNew(stack);
      break;
  
  	case 'n':
  		printPopNoNew(stack);
      break;
  
  	case 'f':
  		print(stack);
  		break;
  
  	case 'c':
      clear(stack);
  		break;
  
  	case 'd':
  		duplicate(stack);
  		break;
  
  	case 'r':
  		reverse(stack);
  		break;
  

  	}

}

bool isOperator(char input) //returns bool for operator or not
{
	char operators[] = { '+', '-', '*', '/', '%', 'p', 'n', 'f', 'c', 'd', 'r' };

	for (int i = 0; i < 11; i++)
	{
		if (input == operators[i])
		{
			return true;
		}
	}

	return false;
}

//Arguments
void printNoPopNew(Stack<int>& stack) //print top value, dont pop, add new line
{
	cout << stack.top() << endl;

}

void printPopNoNew(Stack<int>& stack) //print top value, pop, no new line
{
	cout << stack.topAndPop() << " ";

}

void print(Stack<int>& stack) //prints the whole stack without altering, with new line after each value
{
	Stack<int> tempStack = stack;

	while (!tempStack.isEmpty())
		cout << tempStack.topAndPop() << " ";
  cout << endl;

}

void clear(Stack<int>& stack) //clears the stack
{
	if (!stack.isEmpty())
		stack.makeEmpty();

}

void duplicate(Stack<int>& stack) //duplicates the top item
{
	if (!stack.isEmpty())
		stack.push(stack.top());

}

void reverse(Stack<int>& stack) //reverses tje first two items
{
	int valOne = stack.topAndPop();
	int valTwo = stack.topAndPop();

	stack.push(valOne);
	stack.push(valTwo);
     
}

//Operators
void add(Stack<int>& stack) //performs addition
{
	int lChild, rChild, result;
	rChild = stack.topAndPop();
	lChild = stack.topAndPop();

	result = lChild + rChild;

	stack.push(result);

}

void subtract(Stack<int>& stack) //performs addition
{
	int lChild, rChild, result;
	rChild = stack.topAndPop();
	lChild = stack.topAndPop();

	result = lChild - rChild;

	stack.push(result);

}

void multiply(Stack<int>& stack) //performs addition
{
	int lChild, rChild, result;
	rChild = stack.topAndPop();
	lChild = stack.topAndPop();

	result = lChild * rChild;

	stack.push(result);

}

void divide(Stack<int>& stack) //performs division
{
	try
	{
		int lChild, rChild, result;
		rChild = stack.topAndPop();
		lChild = stack.topAndPop();

		if (rChild == 0)
			throw DivisionByZero();

		result = lChild / rChild;

		stack.push(result);

	}
	catch (DivisionByZero e)
	{
		cout << "Division By Zero Exception -- Stack Unchanged." << endl;
	}

}

void mod(Stack<int>& stack) //performs modulus
{
	try
	{
		int lChild, rChild, result;
		rChild = stack.topAndPop();
		lChild = stack.topAndPop();

		if (rChild == 0)
			throw DivisionByZero();

		result = lChild % rChild;

		stack.push(result);

	}
	catch (DivisionByZero e)
	{
		cout << "Division By Zero Exception -- Stack Unchanged." << endl;
   
	}
}


