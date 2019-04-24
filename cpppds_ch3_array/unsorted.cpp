// Implementation file for Unsorted.h

#include "unsorted.h"

#include <iostream>

using namespace std;

UnsortedType::UnsortedType()
{
  length = 0;
}
bool UnsortedType::IsFull() const
{
  return (length == MAX_ITEMS);
}
int UnsortedType::GetLength() const
{
  return length;
}

ItemType UnsortedType::GetItem(ItemType item, bool& found)
// Pre:  Key member(s) of item is initialized.
// Post: If found, item's key matches an element's key in the
//       list and a copy of that element has been returned;
//       otherwise, item is returned.
{
  bool moreToSearch;
  int location = 0;
  found = false;

  moreToSearch = (location < length);

  while (moreToSearch && !found)
  {
    switch (item.ComparedTo(info[location]))
    {
      case LESS    :
      case GREATER : location++;
                     moreToSearch = (location < length);
                     break;
      case EQUAL   : found = true;
                     item = info[location];
                     break;
    }
  }
  return item;
}

void UnsortedType::MakeEmpty()
// Post: list is empty.
{
  length = 0;
}
void UnsortedType::PutItem(ItemType item)
// Post: item is in the list.
{
  info[length] = item;
  length++;
}
void UnsortedType::DeleteItem(ItemType item)
// Pre:  item's key has been initialized.
//       An element in the list has a key that matches item's.
// Post: No element in the list has a key that matches item's.
{
  int location = 0;

  while (item.ComparedTo(info[location]) != EQUAL)
    location++;

  info[location] = info[length - 1];
  length--;
}
void UnsortedType::ResetList()
// Post: currentPos has been initialized.
{
  currentPos = -1;
}

ItemType UnsortedType::GetNextItem()
// Pre:  ResetList was called to initialized iteration.
//       No transformer has been executed since last call.
//       currentPos is defined.
// Post: item is current item.
//       Current position has been updated.
{
  currentPos++;
  return info[currentPos];
}

bool UnsortedType::IsThere(ItemType item, bool& found)                // NewStuff
//Preconditions:  List has been initialized.
//                Key member of item is initialized.
//Postconditions: If there is an element someItem whose key matches item’s key, then found = true;
//                otherwise found = false.
//                List is unchanged.
{
  bool moreToSearch;
  int location = 0;
  found = false;

  moreToSearch = (location < length);

  while (moreToSearch && !found)
  {
    switch (item.ComparedTo(info[location]))
    {
      case LESS    :
      case GREATER : location++;
                     moreToSearch = (location < length);
                     break;
      case EQUAL   : found = true;
//                     item = info[location];
                     break;
    }
  }
  return found;
}

ItemType UnsortedType::SplitLists(UnsortedType list, ItemType item, UnsortedType& list1, UnsortedType& list2) //NewStuff
// Preconditions : List has been initialized and is not empty.
// Postconditions: list1 contains all the items of list whose keys are
//                 less than or equal to item's key;
//                 list2 contains all the items of list whose keys are
//                 greater than item's key.
{
  bool moreToSearch;
  int location = 0;

  moreToSearch = (location < length);

  while (moreToSearch)
  {
    switch (item.ComparedTo(info[location]))
    {
      case LESS    : list2.PutItem(info[location]);
                     location++;
                     moreToSearch = (location < length);
                     break;
      case GREATER : list1.PutItem(info[location]);
					 location++;
                     moreToSearch = (location < length);
                     break;
      case EQUAL   : list1.PutItem(info[location]);
                     item = info[location];
					 location++;
                     moreToSearch = (location < length);
                     break;
    }
  }

  return item;
}
