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
const int oo = 1010101010;
class FlippingBitsDiv1
{
private:
	string s;//sequence B (-'0')
	int n, m;//N, M
	int t;//n / m
	unsigned bitcnt(unsigned x)
	{
		x = ((x & 0xaaaaaaaau) >> 1) + (x & 0x55555555u);
		x = ((x & 0xccccccccu) >> 2) + (x & 0x33333333u);
		x = ((x & 0xf0f0f0f0u) >> 4) + (x & 0x0f0f0f0fu);
		x = ((x & 0xff00ff00u) >> 8) + (x & 0x00ff00ffu);
		return (x >> 16) + (x & 0x0000ffffu);
	}
	int solveSmallM()//O(2^m*n/m(*log(32)))
	{
		printf("solveSmallM(n=%d, m=%d, t=%d)\n", n, m, t);
		static int a[333];//a[i]: B[ [(i-1)*m, i*m) ]
		static int f[2][2];//f[i & 1][j]: first i*m bits, j = if a[i] is flipped, min steps
		for(int i = 1; i <= t + 1; i++)
		{
			a[i] = 0;
			for(int j = 0; j < m && (i - 1) * m + j < n; j++)
				a[i] |= (s[(i - 1) * m + j] << j);
		}
		int ans = oo;
		for(int S = 0; S < (1 << m); S++)//enum first m bits
		{
			f[0][0] = 0;
			f[0][1] = oo;
			for(int i = 1; i <= t; i++)
			{
				f[i & 1][0] = min(f[~i & 1][0], f[~i & 1][1]) + bitcnt(a[i] ^ S);
				f[i & 1][1] = min(f[~i & 1][0] + 1 + (i > 1), f[~i & 1][1]) + m - bitcnt(a[i] ^ S);
			}
			ans = min(ans, min(f[t & 1][0], f[t & 1][1]) + (int)bitcnt(a[t + 1] ^ (S & ((1 << (n % m)) - 1))));//add last n%m bits
		}
		return ans;
	}
	int solveBigM()//O(2^(n/m)*n)
	{
		printf("solveBigM(n=%d, m=%d, t=%d)\n", n, m, t);
		static int bucket[333];//bucket[i % m]: sum of B[i]
		int ans = oo;
		for(int S = 0; S < (1 << t); S++)//enum whether we flip first i*m bits
		{
			memset(bucket, 0, m * sizeof(int));
			int now = 0, cost = 0;
			for(int i = 0; i < n; i++)
			{
				if(i % m == 0)
				{
					if(S & (1 << (i / m)))
					{
						if(!now)
							cost += 1 + (i > 0), now = 1;
					}
					else
						now = 0;
				}
				if(s[i] != now)
					bucket[i % m]++;
			}
			for(int i = 0; i < m; i++)
				cost += min(bucket[i], t + (n % m > i) - bucket[i]);//B[i] = 1 or B[i] = 0
			ans = min(ans, cost);
		}
		return ans;
	}
public:
	int getmin(vector<string> S, int M)//it can be O(2^sqrt(n)*n^(3/4))... but O(2^sqrt(n)*n) is good enough
	{
		for(int i = 0; i < S.size(); i++)
			s += S[i];
		n = s.size();
		for(int i = 0; i < n; i++)
			s[i] -= '0';
		m = M;
		t = n / m;
		if(m <= t)
			return solveSmallM();
		else
			return solveBigM();
	}
};

