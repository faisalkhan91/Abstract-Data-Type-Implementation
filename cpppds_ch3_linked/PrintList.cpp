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

