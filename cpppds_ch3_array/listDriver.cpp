// Test driver
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>
#include <cstdlib>

#include "unsorted.h"
#include "tools.hpp"

using namespace std;

void PrintList(ofstream& outFile, UnsortedType& list);
bool IsThere2(ItemType item, bool& found, UnsortedType list);

int main()
{
  ifstream inFile;       // file containing operations
  ofstream outFile;      // file containing output
  string inFileName;     // input file external name
  string outFileName;    // output file external name
  string outputLabel;
  string command;        // operation to be executed

  int number;
  ItemType item;
  UnsortedType list;
  bool found;
  int numCommands;

  UnsortedType list1;
  UnsortedType list2;

  banner();

  // Prompt for file names, read file names, and prepare files
  cout << "Enter name of input command file; press return." << endl;
  cin  >> inFileName;
  inFile.open(inFileName.c_str());

  cout << "Enter name of output file; press return." << endl;
  cin  >> outFileName;
  outFile.open(outFileName.c_str(), ios::out | ios::app);

  cout << "Enter name of test run; press return." << endl;
  cin  >> outputLabel;
  outFile << "[" << outputLabel << "]" << endl << endl;
  if (!inFile)
  {
    cout << "file not found" << endl;
	exit(2);
  }
  inFile >> command;

  numCommands = 0;
  while (command != "Quit")
  {
    if (command == "PutItem")
    {
      inFile >> number;
      item.Initialize(number);
      list.PutItem(item);
      item.Print(outFile);
      outFile << " is in list" << endl;
    }
    else if (command == "DeleteItem")
    {
      inFile >> number;
      item.Initialize(number);
      list.DeleteItem(item);
      item.Print(outFile);
      outFile << " is deleted" << endl;
    }
    else if (command == "GetItem")
    {
      inFile >> number;
      item.Initialize(number);
      item = list.GetItem(item, found);
      item.Print(outFile);
      if (found)
        outFile << " found in list." << endl;
      else outFile <<  " not in list."  << endl;
    }
    else if (command == "GetLength")
      outFile << "Length is " << list.GetLength() << endl;
    else if (command == "IsFull")
      if (list.IsFull())
        outFile << "List is full." << endl;
      else outFile << "List is not full."  << endl;
    else if (command == "MakeEmpty")
	  list.MakeEmpty();
	else if (command == "PrintList")
	  PrintList(outFile, list);
    else if (command == "IsThere")                                       //NewStuff
    {
      inFile >> number;
      item.Initialize(number);
      list.IsThere(item, found);
      item.Print(outFile);
      if (found)
        outFile << " is there in the list" << endl;
      else outFile <<  " is not there in the list."  << endl;
    }
    else if (command == "IsThere2")                                       //NewStuff
    {
      inFile >> number;
      item.Initialize(number);
      IsThere2(item, found, list);
      item.Print(outFile);
      if (found)
        outFile << " is there in the list" << endl;
      else outFile <<  " is not there in the list."  << endl;
    }
    else if (command == "SplitLists")                 // NewStuff
    {
      inFile >> number;
      item.Initialize(number);
      list.SplitLists(list, item, list1, list2);
      item.Print(outFile);
      outFile << " - This is the value for the split" << endl;
      PrintList(outFile, list1);
      PrintList(outFile, list2);
    }
	else
	  cout << command << " is not a valid command." << endl;
	numCommands++;
    cout <<  " Command number " << numCommands << " completed."
         << endl;
    inFile >> command;
  };

  cout << "Testing completed."  << endl;
  inFile.close();
  outFile.close();

  bye();

  return 0;
}


void PrintList(ofstream& dataFile, UnsortedType& list)
// Pre:  list has been initialized.
//       dataFile is open for writing.
// Post: Each component in list has been written to dataFile.
//       dataFile is still open.
{
  int length;
  ItemType item;

  list.ResetList();
  length = list.GetLength();
  for (int counter = 1; counter <= length; counter++)
  {
    item = list.GetNextItem();
    item.Print(dataFile);
  }
  dataFile << endl;
}

bool IsThere2(ItemType item, bool& found, UnsortedType list)                // NewStuff
//Preconditions:  List has been initialized.
//                Key member of item is initialized.
//Postconditions: If there is an element someItem whose key matches item’s key, then found = true;
//                otherwise found = false.
//                List is unchanged.
{
  found = false;

  list.GetItem(item, found);

  return found;
}
