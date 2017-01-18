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
const int MOD = 1000000007, MAXN = 1010101;

class LittleElephantAndBoard
{
private:
	int fac[MAXN], facrev[MAXN];
	long long quickmul(int a, int b)
	{
		if(b <= 1)
			return b ? a : 1;
		long long tmp = quickmul(a, b >> 1);
		tmp = tmp * tmp % MOD;
		return b & 1 ? tmp * a % MOD : tmp;
	}
	void init(int n)
	{
		fac[0] = 1;
		for(int i = 1; i <= n; i++)
			fac[i] = (long long)fac[i - 1] * i % MOD;
		facrev[n] = quickmul(fac[n], MOD - 2);
		for(int i = n - 1; i >= 0; i--)
			facrev[i] = (long long)facrev[i + 1] * (i + 1) % MOD;
	}
	int solve(int n, int c1, int c2)//put c1 color1 and c2 color2 into n segments
	{
		int ret = 0;
		int p2 = 1 + ((n ^ c1 ^ c2) & 1);//2^i
		for(int i = (n ^ c1 ^ c2) & 1; i <= n; i += 2, p2 = (long long)p2 * 4 % MOD)
		{
			int num1 = (n - i + c1 - c2) / 2, num2 = (n - i - c1 + c2) / 2, now;
			if(num1 < 0 || num2 < 0 || (now = c1 - num1 - i) < 0)
				continue;
			ret = (ret + (long long)fac[n] * facrev[i] % MOD * facrev[num1] % MOD * facrev[num2] % MOD * fac[now + n - 1] % MOD * facrev[n - 1] % MOD * facrev[now] % MOD * p2) % MOD;
		}
		return ret;
	}
public:
	int getNumber(int M, int R, int G, int B)
	{
		init(M);
		if((R = M - R) < 0 || (G = M - G) < 0 || (B = M - B) < 0)
			return 0;
		return ((long long)solve(R - 1, G, B) + solve(R, G, B) * 2 + solve(R + 1, G, B)) * 2 % MOD;
	}
};

