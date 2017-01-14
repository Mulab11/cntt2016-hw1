#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class KingdomAndTrees
{
	public:
	vector<int> h;
	
	bool check(int X)
	{
		int s=0;
		for(int i=0;i<h.size();i++)//In each step, we should make the current element as small as possible.
		{
			if(h[i]+X<=s)return 0;
			s=max(h[i]-X,s+1);
		}
		return 1;
	}
	
	int minLevel(vector<int> heights)
	{
		h=heights;
		int low=-1,high=(1<<30)-1,mid;
		while(low+1<high)//use dichotomy to determine the minimum k. 
		{
			mid=low+high>>1;
			if(check(mid))high=mid;
			else low=mid;
		}
		return high;
	}
};

