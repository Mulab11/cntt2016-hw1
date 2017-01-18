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
const int MAXN = 1010101, oo = 101010101;
class SparseFactorial
{
private:
	int temp[MAXN];
	vector<int> solve_prime_power(int p, int q, int pq)//p^q = pq, p is prime
	{
		vector<int> ret(pq, oo);
		memset(temp, 0, pq * sizeof(int));
		for(int k = 0; k < p * q; k++)
			for(int num = pq / p; num; num /= p)
				for(int i = 0; i < num; i++)
					if(++temp[((long long)k * k + pq / num * i) % pq] == q)
						ret[((long long)k * k + pq / num * i) % pq] = k;
		return ret;
	}
	vector<int> merge(const vector<int> &a, const vector<int> &b)
	{
		int as = a.size(), bs = b.size();
		vector<int> ret(as * bs, oo);
		for(int i = 0; i < as * bs; i++)
			ret[i] = max(a[i % as], b[i % bs]);
		return ret;
	}
public:
	long long getCount(long long lo, long long hi, long long divisor)
	{
		vector<int> ret(1, 0);
		int d = divisor;
		for(int i = 2; i * i <= d; i++)//factorize
			if(d % i == 0)
			{
				int cnt = 0, now = 1;
				while(d % i == 0)
					d /= i, cnt++, now *= i;
				ret = merge(ret, solve_prime_power(i, cnt, now));
			}
		if(d > 1)//big prime
			ret = merge(ret, solve_prime_power(d, 1, d));
		long long ans = 0;
		for(int i = 0; i < divisor; i++)
			ans += max((hi - i + divisor) / divisor - (max(lo - 1, (long long)ret[i] * ret[i]) - i + divisor) / divisor, 0ll);
		return ans;
	}
};

