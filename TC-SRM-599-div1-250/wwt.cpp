#include <bits/stdc++.h>

using namespace std;

class BigFatInteger
{
public:
	int minOperations(int A, int B)
	{
		static int c[20];
		int tot = 0;
		for(int i = 2;i <= A;i ++)
			if (A % i == 0)
			{
				c[++ tot] = 0;
				for(;A % i == 0;A /= i,c[tot] ++);
				c[tot] *= B;
			}
		int ans = 0;
		sort(c + 1,c + tot + 1);
		for(int i = 1;i <= tot;i ++) //every prime is independent
		{
			int cur = 0,base = 1;
			for(;c[i] > base;base *= 2,++ cur); //choose the possibly largest to put
			ans = max(ans,cur);
		}
		return ans + tot;//we must use type 1 for tot times first
	}
};
