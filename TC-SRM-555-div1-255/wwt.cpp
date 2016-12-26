/*
因为|S|<=50，所以直接暴力dp就好了。
*/
#include <bits/stdc++.h>

using namespace std;

class CuttingBitString
{
public:
	bool test(string S,int l,int r) //判断S[l..r]是不是一个5的幂
	{
		l --,r --;
		long long x = 0;
		for(;l <= r;l ++) 
			x = x * 2 + (S[l] == '1');
		for(;x && x % 5 == 0;x /= 5);
		return x == 1;
	}

	int getmin(string S)
	{
		int n = S.length();
		static bool ok[55][55];
		memset(ok,0,sizeof ok);
		ok[0][0] = 1;
		for(int i = 1;i <= n;i ++)
		{
			for(int j = 1;j <= n;j ++)
				for(int k = 0;k < j;k ++)
					if (ok[i - 1][k] && S[k] == '1' && test(S,k + 1,j)) //dp
						ok[i][j] = 1;
			if (ok[i][n]) return i;
		}
		return -1;
	}
};
