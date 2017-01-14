#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

class TheTree
{
	public:
	
	int work(vector<int> C)
	{
		//find maximum d that for each 0<=x<d cnt[x]>=2
		for(int i=0;i<=C.size();i++)
			if(i==C.size()||C[i]==1)
				return C.size()+i;
	}
	
	int maximumDiameter(vector<int> cnt)
	{
		//Let's assume that the diameter go through X
		//If V=X, it's clear that if there is an integer d that cnt[0..d-1]>=2, the diameter can be 2d
		//Then we can pick all possible distance len from V to X,
		//and simply delete first len elements of cnt and solve it as V=X
		int ans=0;
		while(!cnt.empty())
		{
			ans=max(ans,work(cnt));
			cnt.erase(cnt.begin());
		}
		return ans;
	}
};

