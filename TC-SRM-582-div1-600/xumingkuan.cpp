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
#include <cassert>
using namespace std;
const int MOD = 1000000009;
const int MAXN = 1300;
class ColorfulBuilding
{
private:
	long long quickmul(int a, int b)
	{
		if(b <= 1)
			return b ? a : 1;
		long long tmp = quickmul(a, b >> 1);
		tmp = tmp * tmp % MOD;
		return b & 1 ? tmp * a % MOD : tmp;
	}
	string concatenate(const vector<string> &vec)
	{
		string ret;
		for(int i = 0; i < (int)vec.size(); i++)
			ret += vec[i];
		return ret;
	}
	int char_to_int(char ch)
	{
		return isupper(ch) ? ch - 'A' : ch - 'a' + 26;
	}
	int n, mp[52 * 52 + 1], col[MAXN];//color, 1-based
	int f;//f(i)(j): buildings with height <= i, the first empty place is after the building i, we can see j colors, number of arrangements
	int sum[MAXN];//sum(i)[j]: sum(k=0~i) f[k][j] * (n-k-1)!
	int sumcol[MAXN][MAXN];//sum(i)[c][j]: sum(k=0~i,col[k]==c) f[k][j] * (n-k-1)!
	int fac[MAXN], facrev[MAXN];//fac[i] = i!, facrev[i] = (i!)^(-1)
public:
	int count(vector<string> color1, vector<string> color2, int L)
	{
		string c1 = concatenate(color1), c2 = concatenate(color2);
		n = c1.size();
		memset(mp, 0, sizeof(mp));
		int mpcnt = 0;
		for(int i = 0; i < n; i++)
		{
			int now = char_to_int(c1[i]) * 52 + char_to_int(c2[i]);
			col[i + 1] = mp[now] ? mp[now] : mp[now] = ++mpcnt;
		}
		fac[0] = facrev[0] = 1;
		for(int i = 1; i <= n; i++)
		{
			fac[i] = (long long)fac[i - 1] * i % MOD;
			facrev[i] = (long long)facrev[i - 1] * quickmul(i, MOD - 2) % MOD;
		}
		memset(sum, 0, sizeof(sum));
		memset(sumcol, 0, sizeof(sumcol));
		assert(n > 0);
		sum[0] = fac[n - 1];//f[0][0] = 1;
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= i && j <= L; j++)
			{
				//f[i][j] = sum(k=0~i-1) f[k][j-(col[k]!=col[i])] * A(n-k-1,i-k-1) (== A(n-k-1,n-i))
				f = ((long long)sum[j - 1] - sumcol[col[i]][j - 1] + sumcol[col[i]][j] + MOD) * facrev[n - i] % MOD;
				sum[j] = (sum[j] + (long long)f * fac[n - i - 1]) % MOD;
				sumcol[col[i]][j] = (sumcol[col[i]][j] + (long long)f * fac[n - i - 1]) % MOD;
			}
		return f;
	}
};

