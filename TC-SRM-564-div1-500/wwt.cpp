/*
不同的三元组等价于最后不同的序列数。考虑怎么计序列的数量。dp，设f[i][s][pos]表示确定到第i位，这一位之前,s集合中这些颜色都是有的，
pos表示上一位的颜色，那么这一位的转移，正常而言，就是s中pos的下一个，然后我们可以让这下一个数量变为0，那么就变成下下个
，同理，再令下下个为0，就填pos，直接转移即可。
*/
#include <bits/stdc++.h>

using namespace std;

const int maxn = 100005;

typedef long long ll;

ll f[maxn][1 << 3][3];

class AlternateColors2
{
public:
	int get_nxt(int s,int p)
	{
		for(;;)
		{
			p = (p + 1) % 3;
			if (s & (1 << p)) return p;
		}
	}

	long long countWays(int n, int k)
	{
		f[1][7][2] = 1;
		for(int i = 1;i <= n;i ++)
			for(int s = 1;s < 8;s ++)
				for(int tu = 0;tu < 3;tu ++)
					if (f[i][s][tu])
					{
						int nx = get_nxt(s,tu);
						//normal trans
						if (i != k || i == k && nx == 0)
							f[i + 1][s][nx] += f[i][s][tu];
						//make nx not exist
						if (nx != tu)
						{
							int ns = (s ^ (1 << nx));
							int nxx = get_nxt(s,nx);
							if (i != k || i == k && nxx == 0)
								f[i + 1][ns][nxx] += f[i][s][tu];
							//make nxx not exist
							if (nxx != tu)
							{
								ns = (1 << tu);
								if (i != k || i == k && tu == 0)
									f[i + 1][ns][tu] += f[i][s][tu];
							}
						}
					}
		long long ans = 0;
		for(int s = 0;s < 8;s ++)
			for(int i = 0;i < 3;i ++) ans += f[n + 1][s][i];
		return ans;
	}
};
