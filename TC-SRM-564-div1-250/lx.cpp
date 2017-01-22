#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

class KnightCircuit2
{
public :
	int maxSize(int n, int m)
	{
		if (n > m)
			swap(n, m);
		if (n == 1)
			return 1;
		if (n == 2)
			return 1 + (m - 1) / 2;
		if (m == 3)
			return 8;
		return n * m;
	}
};
