/*
随便模拟一下就好了。一种是填0，另一种就设填x，写好特判即可（样例很良心）。
*/
#include <bits/stdc++.h>

using namespace std;

class Suminator
{
public:
	vector<int> a;
	int want;

	int test(int ty) //ty = 0表示直接填0，否则设填的数为x
	{
		static long long stk[1005][2]; //ans=stk[0]*x+stk[1]
		int top = 0;
		for(int i = 0;i < a.size();i ++)
			if (a[i] > 0 || (ty == 1 && a[i] == -1))
			{
				++ top;
				if (a[i] > 0) stk[top][0] = a[i]; else stk[top][0] = 0;
				if (a[i] == -1) stk[top][1] = 1; else stk[top][1] = 0;
			} else
			{
				long long x = stk[top - 1][0] + stk[top][0],y = stk[top - 1][1] + stk[top][1];
				top = max(top - 2,0);
				stk[++ top][0] = x,stk[top][1] = y;
			}
		//判断方程是否可解
		if (!ty)
		{
			if (stk[top][0] == want) return 1; else return 0;
		}
		if (!stk[top][1] && stk[top][0] == want) return 1;
		if (stk[top][0] >= want) return -1; else 
			if (!stk[top][1] && stk[top][0] != want) return -1; else
				return want - stk[top][0];
	}	

	int findMissing(vector<int> program,int wantedResult)
	{
		a = program,want = wantedResult;
		if (test(0)) return 0; else
			return test(1);
	}
};
