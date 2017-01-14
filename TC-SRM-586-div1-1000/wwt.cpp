#include <bits/stdc++.h>

using namespace std;

const int maxn = 55;

int f[maxn][27][27];//f[i][j][k]:做到第i个串，有j个字母还没出现，有k个出现了的字母要继续用

class StringWeight
{
public:
	vector<int> l;

	int dfs(int plen,int i,int j,int k) //O(|L| * |sigma|^ 5),plen:之前串的总长
	{
		if (i == l.size())
		{
			if (k) return (1 << 30); //illegal
			return 0;
		}
		int &tmp = f[i][j][k];
		if (~tmp) return tmp;
		tmp = (1 << 30);
		int need = min(l[i],26); //a light string
		for(int a = 0;a <= j;a ++) //选a个新的且只在i出现的字符
			for(int b = 0;b <= k;b ++) //b个中间字符
				for(int c = 0;a + c <= j && a + b + c <= need;c ++) //c个开头字符
				{
					int d = need - a - b - c; //d个结束字符
					if (d > k || b > k - d) continue;
					int cost = plen * d + d * (d + 1) / 2 - (plen + l[i]) * c + c * (c - 1) / 2; //开头和结尾每个字符肯定长度为1
					if (b == 0) cost += l[i] - c - d - a;
					tmp = min(tmp,dfs(plen + l[i],i + 1,j - a - c,k + c - d) + cost);
					if (tmp == 4)
					{
						int u;
						u ++;
					}
				}	
		return tmp;
	}

	int getMinimum(vector<int> L)
	{
		l = L;
		memset(f,255,sizeof f);
		return dfs(0,0,26,0);		
	}
};
