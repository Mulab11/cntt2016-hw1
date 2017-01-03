#include<algorithm>
#include<vector>
using namespace std;
class KnightCircuit2
{
public:
	int maxSize(int w, int h)
	{
		int n=w,m=h;
		if(n>m)
			swap(n,m);
		if(n==3&&m==3)
			return 8;
		if(n==1)
			return 1;
		if(n==2)
			return m+1>>1;
		else
			return n*m;
	}
};
