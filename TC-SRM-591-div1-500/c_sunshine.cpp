#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;
class PyramidSequences
{
	public:
	int gcd(int a,int b)//greatest common divisor
	{return b?gcd(b,a%b):a;}
	
	LL distinctPairs(int N, int M)
	{
		//Let's imagine A[i],B[i] as point (A[i],B[i]) on the two-dimensional plane, .
		//Let g be gcd(N-1,M-1), and the rectangle (1,1)-(N,M) can be divided into many squares of size g*g
		//We can find that there is exactly g-1 points strictly inside each square which are passed by the path.
		//And the vertices of squares are passed by the path if and only if (i-1)/g = (j-1)/g mod 2.
		//It is easy to get the answer: floor(((N-1)/g*(M-1)/g+1)/2)
		N--,M--;
		int g=gcd(N,M);
		int p=N/g,q=M/g;
		return ((LL)(p+1)*(q+1)+1)/2+(LL)(g-1)*p*q;
	}
};

