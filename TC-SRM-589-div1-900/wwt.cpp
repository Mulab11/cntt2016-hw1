#include <bits/stdc++.h>

using namespace std;

const int maxn = 305;

class FlippingBitsDiv1
{
public:
	string s;
	int m;

	int getmin(vector<string> S, int M)
	{
		int ans = (1 << 30);
		m = M;
		s = "";
		for(auto p : S) s = s + p;
		int n = s.length();
		if (m < s.length() / m) //m is small
		{
			for(int i = 0;i < (1 << m);i ++) //fix the number of each row
			{
				static int cnt[maxn][2];//if column i is flipped(or not),what's the cost for the numbers in this column to become the fixed one
				memset(cnt,0,sizeof cnt);
				for(int j = 0;j < n;j ++)
				{
					int fix = bool(i & (1 << (j % m)));
					cnt[j / m][0] += bool((s[j] - '0') != fix);
					cnt[j / m][1] += bool((s[j] - '0') == fix);
				}
				static int f[maxn][2];//dp frontward,consider column i,flipped(or not)
				memset(f,60,sizeof f);
				int inf = f[0][0],final = (n - 1) / m;
				f[final + 1][0] = 0;
				for(int j = final;j >= 0;j --)
					for(int flip = 0;flip < 2;flip ++)
						if (f[j + 1][flip] < inf)
							for(int cflip = 0;cflip < 2;cflip ++) //whether to flip this column
								if ((n % m) && (j == final) && cflip) continue; else
								f[j][flip ^ cflip] = min(f[j][flip ^ cflip],f[j + 1][flip] + cnt[j][flip ^ cflip] + cflip);
				ans = min(ans,min(f[0][0],f[0][1]));
			}
		} else //n / m is small
		{
			for(int i = 0;i < (1 << (n / m));i ++) //determine the columns to flip
			{
				static int cnt[maxn][2];//the number of 0s or 1s in each row
				memset(cnt,0,sizeof cnt);
				for(int j = n - 1,sta = 0;j >= 0;j --)
				{
					if (j % m == m - 1) sta ^= bool(i & (1 << (j / m))); 
					cnt[j % m][(s[j] - '0') ^ sta] ++;
				}
				int cur = 0;
				for(int i = 0;i < m;i ++) cur += min(cnt[i][0],cnt[i][1]); //all number in row i must be the same
				ans = min(ans,cur + __builtin_popcount(i));
			}
		}
		return ans;
	}
};
