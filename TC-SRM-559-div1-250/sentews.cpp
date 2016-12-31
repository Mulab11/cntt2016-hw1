#include <iostream>
#include <algorithm>
using namespace std;
class HyperKnight
{
	public:
	long long countCells(int a, int b, int numRows, int numColumns, int k)
	{
		if(a > b)
			swap(a, b);
		long long n=numRows,m=numColumns;
		switch(k)
		{
		case 8:
			return (n-b*2)*(n-b*2);
		case 6:
			return 2LL*(b-a)*(n+m-4*b);
		case 4:
			return 2LL*a*(n+m-4*b)+4LL*(b-a)*(b-a);
		case 3:
			return 8LL*a*(b-a);
		case 2:
			return a*a*4;
		default:
			return 0;
		}
	}
};
