#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;
/*
SSR(A, B) is int
<=> 2sqrt(AB) is int
<=> AB is square
*/
const int MAXN = 80808;
bool f[MAXN];//have square factors
class TheSquareRootDilemma
{
	public:
	int floorsqrt(int x)
	{
		return (int)(sqrt(x) + 1e-8);
	}
	void init(int lim = MAXN - 1)//sieve
	{
		memset(f, false, sizeof(f));
		for(int i = 2; i * i <= lim; i++)
			for(int j = 1; i * i * j <= lim; j++)
				f[i * i * j] = true;//square factor i * i
	}
	int countPairs(int N, int M)
	{
		const int lim = min(N, M);
		init(lim);
		int ret = 0;
		for(int i = 1; i <= lim; i++)//enumerate variable "a" in the solution
			if(!f[i])//i doesn't have square factors
				ret += floorsqrt(N / i) * floorsqrt(M / i);
		return ret;
	}
};
