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
typedef int key_t;
typedef int value_t;
const int MAXN = 1010;
value_t sigmamu[MAXN];//sigmamu[i] = sigma_{j=1}^i mu(j).
value_t sigmamu2[MAXN];//sigmamu2[i] = sigma_{j=1}^i mu^2(j).
int prime[MAXN], primenum;
int minprime[MAXN];
int maxinitnum;
key_t floorsqrt_[MAXN];
void init(int n)
{
	maxinitnum = n;
	memset(minprime, 0, (n + 1) * sizeof(int));
	primenum = 0;
	sigmamu[0] = sigmamu2[0] = 0;
	sigmamu[1] = sigmamu2[1] = 1;
	for(int i = 2; i <= n; i++)
	{
		if(!minprime[i])
			prime[++primenum] = minprime[i] = i;
		sigmamu[i] = i / minprime[i] % minprime[i] == 0 ? 0 : -sigmamu[i / minprime[i]];
		sigmamu2[i] = sigmamu[i] * sigmamu[i];
		for(int j = 1; i * prime[j] <= n; j++)
		{
			minprime[i * prime[j]] = prime[j];
			if(i % prime[j] == 0)
				break;
		}
	}
	for(int i = 2; i <= n; i++)
	{
		sigmamu[i] += sigmamu[i - 1];
		sigmamu2[i] += sigmamu2[i - 1];
	}
	for(int i = 0; i * i <= n; i++)
		for(int j = i * i; j < (i + 1) * (i + 1); j++)
			floorsqrt_[j] = i;
}
key_t floorsqrt(key_t x)
{
	if(x <= maxinitnum)
		return floorsqrt_[x];
	return (key_t)(sqrt(x) + 1e-8);
}
key_t sqr(key_t x)
{
	return x * x;
}
value_t getsigmamu2(key_t n)
{
	if(n <= maxinitnum)
		return sigmamu2[n];
	value_t ret = 0;
	for(key_t i = 1; i * i <= n; i++)//O(n^(1/3))
	{
		key_t ed = floorsqrt(n / (n / i / i));//n / i / i == n / ed / ed
		ret += (n / i / i) * (sigmamu[ed] - sigmamu[i - 1]);
		i = ed;
	}
	return ret;
}
value_t solve(key_t n, key_t m)
{
	value_t ret = 0, last = 0;
	key_t fn, fm;//fn = floorsqrt(n / i), fm = floorsqrt(m / i)
	for(key_t i = 1; i <= n && i <= m; i++)
	{
		key_t ed = min(n / sqr(fn = floorsqrt(n / i)), m / sqr(fm = floorsqrt(m / i)));//floorsqrt(n / i) == floorsqrt(n / ed), floorsqrt(m / i) == floorsqrt(m / ed)
		value_t now = getsigmamu2(ed);
		ret += fn * fm * (now - last);
		last = now;
		i = ed;
	}
	return ret;
}
class TheSquareRootDilemma
{
    public:
    int countPairs(int N, int M)
	{
    	init((int)(pow(max(N, M), 1.0 / 3.0) * pow(min(N, M), 2.0 / 9.0)) + 1);
        return solve(N, M);
    }
};

