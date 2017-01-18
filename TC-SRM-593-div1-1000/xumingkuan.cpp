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
const int MOD = 1000000007, MAXN = 2020202;

class WolfDelaymasterHard
{
private:
	int n;
	char s[MAXN];//1-based; 2MB
//	int osum[MAXN], wsum[MAXN];//prefix sum; 8MB each
	int nexto[MAXN], nextw[MAXN];//next 'o', next 'w'; 8MB each
	int f[MAXN / 2];//f[i / 2] - f[i / 2 - 1]: number of different valid words of the first i letters
	int g[MAXN / 2];
	void gen(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd)
	{
		memset(s, '?', (N + 1) * sizeof(char));
		long long x = w0;
		for(int i = 0; i < wlen; i++)
		{
			s[x + 1] = 'w';
			x = (x * wmul + wadd) % N;
		}
		x = o0;
		for(int i = 0; i < olen; i++)
		{
			s[x + 1] = 'o';
			x = (x * omul + oadd) % N;
		}
	}
	void init()
	{
		nexto[n + 1] = nextw[n + 1] = n + 1;
		for(int i = n; i >= 1; i--)
		{
			nexto[i] = (s[i] == 'o' ? i : nexto[i + 1]);
			nextw[i] = (s[i] == 'w' ? i : nextw[i + 1]);
		}
		/*osum[0] = wsum[0] = 0;
		for(int i = 1; i <= n; i++)
		{
			osum[i] = osum[i - 1] + (s[i - 1] == 'o');
			wsum[i] = wsum[i - 1] + (s[i - 1] == 'w');
		}*/
	}
public:
	int countWords(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd)
	{
		gen(n = N, wlen, w0, wmul, wadd, olen, o0, omul, oadd);
		init();
		int prevw = 0;//last 'w'
		int prevo = 0;//last 'o'
		int prevwo = 0;//last 'o' before last 'w'
		long long add = 0;
//		printf("%s\n", s + 1);
		//i = 0:
		f[0] = 1;
		(g[((min((nexto[1] - 1) * 2, nextw[1] - 1)) >> 1)] += f[0]) %= MOD;
		add = (add + 1 - g[0] + MOD) % MOD;
		for(int i = 1; i <= n; i++)
		{
			if(s[i] == 'w')
				prevwo = prevo, prevw = i;
			else if(s[i] == 'o')
				prevo = i;
			if(i & 1)//length of valid word must be even
				continue;
			f[i >> 1] = add;
			if(prevw)//last valid word includes at least 1 'w'
			{
				int nowr = ((min(i - (i - nexto[prevw] + 1) * 2, prevw - 1)) >> 1);
				int nowl = ((max(prevwo, i - (i - prevw) * 2) + 1) >> 1);
				if(nowl <= nowr)
					f[i >> 1] = ((long long)f[i >> 1] + f[nowr] - (nowl ? f[nowl - 1] : 0) + MOD) % MOD;
//				printf("nowl=%d nowr=%d\n", nowl, nowr);
			}
//			printf("f[%d] = %d  add=%I64d\n", i >> 1, f[i >> 1], add);
			if(i == n)
				return f[i >> 1];
			(g[((min(i + (nexto[i + 1] - i - 1) * 2, nextw[i + 1] - 1)) >> 1)] += f[i >> 1]) %= MOD;
			add = (add + f[i >> 1] - g[i >> 1] + MOD) % MOD;
			f[i >> 1] = (f[i >> 1] + f[(i >> 1) - 1]) % MOD;//prefix sum
		}
		return 0;//n is odd
	}
};

