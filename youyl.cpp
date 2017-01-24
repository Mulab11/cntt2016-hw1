#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
struct KingdomAndTrees
{
	int n,a[120],le,ri;
	int lb[120],rb[120],pre;
	inline bool check(int x)
	{
		for (int i=1;i<=n;i++)
		{
			lb[i]=a[i]-x;
			rb[i]=a[i]+x;
		}
		pre=0;
		for (int i=1;i<=n;i++)// check if x is enough for the problem
		{
			int tmp=max(pre+1,lb[i]);
			if(tmp>rb[i])return false;
			pre=tmp;
		}return true;
	}
	int minLevel(vector<int>heights)
	{
		n=heights.size();
		for (int i=1;i<=n;i++)
		{
			a[i]=heights[i-1];
		}
		le=0;
		ri=1000000000;
		while (le<ri)
		{
			int mi=(le+ri)/2;
			if(check(mi))
			{
				ri=mi;
			}
			else
			{
				le=mi+1;
			}
		}
		return le;
	}
};