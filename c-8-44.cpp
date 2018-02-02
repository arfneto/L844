//
// Lecture 8.42 . . . . . 
//



#include "stdafx.h"
#include "Ring.h"
#include <typeinfo>
#include <iostream>
#include <string>
#include <vector>

using namespace std;





void showRingFor(Ring<string> & r)
{
	int limit = r.size();
	int init = 0;

	cout << "\n*** display ring via for(;;). Size is " << r.size() << " ***" << endl;
	
	if (r.capacity() == limit)init = r.getPos();

	for (
		int i = 0;
		i < limit;
		i++ 
		)
	{
		cout << r.get((init+i)%limit) << endl;
	}
	cout << "*** end of display ring via for(;;) ***" << endl;
	return;
}




//
//	display Ring using iterators
//
void showRingIt(Ring<string> & r)
{
	cout << "\n*** display Ring using iterator. Size is " << r.size() << " ***" << endl;
	if (r.size() < 1)
	{
		cout << "*** end of display ring via iterator ***" << endl;
		return;
	}
	for (
		Ring<string>::iterator it = r.begin();
		it != r.end();
		++it
		)
	{
		cout << *it << endl;
	}
	cout << "*** end of display ring via iterator ***" << endl;
	return;
}





void showRingRBL(Ring<string> & r)
{
	// code
	cout << "\n*** display ring via range-based loop. Size is " << r.size() << " ***" << endl;
	for (string value : r)
	{
		cout << value << endl;
	}
	cout << "*** end of display ring via RBL ***" << endl;
	return;
}






int main(int argc, char **argv)
{
	if (argc != 3)
	{
		cout <<
			"\nUsage:\n\n\"" <<
			(char *)argv[0] <<
			" x y\" where x is the capacity of the circular buffer 5<=x<=" <<
			L_844_MAX_CAPACITY << 
			"\n               and y is total of data points to be inserted 4<=y<=" <<
			L_844_MAX_DATA_POINTS <<
			endl;
		return 1;
	}
	int bufferCapacity = atoi(argv[1]);
	int testSetSize = atoi(argv[2]);	

	cout << "\n8.44 making classes iterable" << endl;
	//
	// verify x = buffer capacity
	//
	if ((bufferCapacity > 4) && (bufferCapacity <= L_844_MAX_CAPACITY))
	{
		cout << "\n\nBuffer capacity is " << bufferCapacity << endl;
	}
	else
	{
		cout <<
			"Buffer Capacity of " <<
			bufferCapacity <<
			" is out of range" <<
			endl;
		return 2;
	}
	//
	// verify y = number of elements to be inserted
	//
	if ((testSetSize >= 4) && (testSetSize <= L_844_MAX_DATA_POINTS))
	{
		cout << "Total of data points is " << testSetSize << endl;
	}
	else
	{
		cout <<
			"Number of " <<
			testSetSize <<
			" data points is out of range" <<
			endl;
		return 3;
	}
	//
	// ==================================== STARTING TESTS ==============================
	//
	{
		char str[20] = "Data XXXX";
		//              01234567
		Ring<string> textRing(bufferCapacity);


		//
		// testing for empty buffer						EMPTY
		//
		cout << "\nStarting test with empty buffer...\nRing has " << textRing.size() << " elements" << endl;
		showRingFor(textRing);
		showRingIt(textRing);
		showRingRBL(textRing);


		//
		// testing for 3-elementa buffer				NOT EMPTY, NOT FULL
		//
		textRing.add("Data 1");
		textRing.add("Data 2");
		textRing.add("Data 3");
		cout << "\nStarting test with buffer not full...\nRing has " << textRing.size() << " elements" << endl;
		showRingFor(textRing);
		showRingIt(textRing);
		showRingRBL(textRing);


		//
		// testing for buffer with run time size		NOT EMPTY, NOT FULL
		//
		for (int i = 4; i <= testSetSize; i++)
		{
			snprintf((str+5), 16, "%d", i);
			textRing.add(str);
		}
		// all data passed thru the buffer. Last N should be there
		cout << "\nStarting test with buffer full...\nRing has " << textRing.size() << " elements" << endl;
		showRingFor(textRing);
		showRingIt(textRing);
		showRingRBL(textRing);
	}
	//{
	//	char asw;
	//	cout << "Enter x to quit" << endl;
	//	cin >> asw;
	//}
	return 0;
}	// end main()

