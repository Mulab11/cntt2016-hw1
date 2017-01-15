#include <bits/stdc++.h>

using namespace std;

class PyramidSequences
{
public:
	int gcd(int a,int b)
	{
		return b ? gcd(b,a % b) : a;
	}

	long long distinctPairs(int N, int M)
	{
		int p = gcd(N - 1,M - 1);//the side length of each square
		int n = (N - 1) / p,m = (M - 1) / p;
		return (p - 1) * 1ll * n * m + ((n + 1) * 1ll * (m + 1) + 1) / 2; //points in a square and lattice points
	}
};
