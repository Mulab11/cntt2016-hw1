#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <cctype>
#include <cassert>
using namespace std;
int gcd(int a, int b)
{
	return !b ? a : gcd(b, a % b);
}
long long sqr(int x)
{
	return (long long)x * x;
}
class PyramidSequences
{
public:
	long long distinctPairs(int N, int M)
	{
		if(N > M)
			swap(N, M);
		int d = gcd(--N, --M);
		N /= d, M /= d;
		return sqr(N) / 4 + (long long)((M - N) / 2 + 1) * (N + 1) + sqr(N + ((N ^ M) & 1)) / 4 + (long long)N * M * (d - 1);//zhao gui lv de chu gong shi...... QAQ
	}
};

