#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <ctime>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <typeinfo>

using namespace std;

class FoxPaintingBalls
{
	public:
	long long theMax(long long R, long long G, long long B, int N)
	{
		if(N == 1)
			return R + G + B;			
		long long a[3] = {R, G, B};
		sort(a, a + 3);
		long long m = (long long)N * (N + 1) / 2;
		long long x = m / 3;
		if(m % 3 == 0)
			return a[0] / x;
		else
		{
			long long tmp = min(a[0] / x, (a[0] + a[1] + a[2]) / m);
			return tmp;
		}
	}
};

