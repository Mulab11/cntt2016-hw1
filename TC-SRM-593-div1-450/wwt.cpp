#include <bits/stdc++.h>

using namespace std;

const int maxn = 55,inf = 50 * 10000 * 2,maxs = 2 * inf + 5;

bitset<maxs> f[maxn];

class MayTheBestPetWin
{
public:
	int calc(vector<int> A,vector<int> B)
	{
		//ans = min(max(\sum_{i in S} B_i - \sum_{i in T} A_i,\sum_{i in T} B_i - \sum_{i in S} A_i))
		//max(x,y)=(x+y+|x-y|)/2
		//ans = (\sum B_i - \sum A_i + |x-y|) / 2
		//f[i][j],considering the ith person,could |x-y| be j? 
		int s = 0,n = A.size();
		memset(f,0,sizeof f);
		f[0][inf] = 1;
		for(auto p : A) s -= p;
		for(auto p : B) s += p;
		for(int i = 0;i < n;i ++)
			for(int s = 0;s <= 2 * inf;s ++)
				if (f[i][s])
				{
					f[i + 1][s + A[i] + B[i]] = 1; //push i in S
					f[i + 1][s - A[i] - B[i]] = 1; //push i in T
				}
		int ans = (1 << 30);
		for(int st = 0;st <= 2 * inf;st ++)
			if (f[n][st])
				ans = min(ans,(s + abs(st - inf)));
		return ans / 2;
	}
};
