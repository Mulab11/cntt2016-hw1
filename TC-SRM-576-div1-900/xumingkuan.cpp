#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <queue>
#include <map>
#include <set>
using namespace std;
const int MOD = 1000000009;
long long quickmul(int a, int b)
{
	if(b <= 1)
		return b ? a : 1;
	long long tmp = quickmul(a, b >> 1);
	tmp = tmp * tmp % MOD;
	return b & 1 ? tmp * a % MOD : tmp;
}
const int REV25 = quickmul(25, MOD - 2);
int now[11];
int pos[11];
bool cmp(int i, int j)//for sort
{
	return now[i] == now[j] ? i < j : now[i] < now[j];
}
class CharacterBoard
{
private:
	int n, m, ans;
	bool eq[11][11][11];//eq[i][j][k]: if row[i] == row[j] + k
	int p26[32];//p26[i] = 26^(2^i)
	int pow26(int x)//26^x
	{
		long long ret = 1;
		for(int i = 0; (1 << i) <= x; i++)
			if(x & (1 << i))
				ret = ret * p26[i] % MOD;
		return ret;
	}
	int sumpow26(int l, int r)//26^l + 26^(l+1) + ... + 26^r
	{
		return (long long)(pow26(r + 1) - pow26(l) + MOD) * REV25 % MOD;
	}
public:
	int countGenerators(vector<string> fragment, int W, int, int)//i0 and j0 are useless
	{
		n = fragment.size();
		m = fragment[0].size();
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				for(int k = 0; k < m; k++)
				{
					eq[i][j][k] = true;
					for(int l = k; l < m; l++)
						if(fragment[i][l] != fragment[j][l - k])
						{
							eq[i][j][k] = false;
							break;
						}
				}
		p26[0] = 26;
		for(int i = 1; i < 30; i++)
			p26[i] = (long long)p26[i - 1] * p26[i - 1] % MOD;
		ans = 0;
		//int cnt = 0;
		for(int len = 1; len <= W; len++)//enumerate the length of generator
		{
			//cnt++;
			for(int i = 0; i < n; i++)
			{
				now[i] = (long long)W * i % len;
				pos[i] = i;
			}
			sort(pos, pos + n, cmp);
			int cross = 0;//overlapped length
			bool ok = true;
			if(now[pos[0]] - now[pos[n - 1]] + len < m)
			{
				cross += m - (now[pos[0]] - now[pos[n - 1]] + len);
				if(!eq[pos[n - 1]][pos[0]][now[pos[0]] - now[pos[n - 1]] + len])
					continue;
			}
			for(int i = 0; i < n - 1; i++)
				if(now[pos[i + 1]] - now[pos[i]] < m)
				{
					cross += m - (now[pos[i + 1]] - now[pos[i]]);
					if(!eq[pos[i]][pos[i + 1]][now[pos[i + 1]] - now[pos[i]]])
					{
						ok = false;
						break;
					}
				}
			if(!ok)
				continue;
			if(cross)
			{
				ans = (ans + pow26(len - n * m + cross)) % MOD;
				continue;
			}
			//cnt--;
			int ed = W;
			for(int i = 1; i < n; i++)
				ed = min(ed, (int)(((long long)W * i - m) / (((long long)W * i - m) / len)));
			//when the length of generator is in interval [len, ed], there won't be anything overlapping
			ans = (ans + sumpow26(len - n * m, ed - n * m)) % MOD;
			len = ed;
		}
		//printf("%d\n", cnt);
		return ans;
	}
};

