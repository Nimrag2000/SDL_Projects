#include <iostream>
#include <string>
using namespace std;

int main()
{
	int size	= 0;
	unsigned int ** row;
	int r;
	int c;
	string *lineText;

	cout << "Enter the size of the Pascal Triangle: ";
	cin >> size;

	row      = (unsigned int **)malloc( sizeof( int * ) * size );
	lineText = new string[size];


	for( r = 0; r < size; r++ )
	{
		row[r] = new unsigned int[ r + 1 ];

		for( c= 0; c <= r; c++ )
		{
			if( ( r == 0 ) || ( c == 0 ) || ( c == r ) )
			{
				row[r][c] = 1;
			}
			else
			{
				row[r][c] = row[r - 1][c - 1] + row[r - 1][c];
			}
			lineText[r] += to_string( row[r][c] );
			lineText[r] += " ";
		}
//		cout << lineText[r] << " --- " << lineText[r].length() - 1 << "\n";
	}

	free( row );

	return 0;
}
