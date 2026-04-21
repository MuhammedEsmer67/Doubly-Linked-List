#include "clsDblLinkedList.h"

int main()
{

	clsDblLinkedList <int> myList;

	myList.InsertEnd(10);
	myList.InsertEnd(20);
	myList.InsertBeginning(5);

	myList.PrintList();   // Output: 5 10 20
	myList.Reverse();
	myList.PrintList();   // Output: 20 10 5

	cout << myList.Size() << endl;    // Output: 3
	cout << myList.isEmpty() << endl; // Output: 0
}