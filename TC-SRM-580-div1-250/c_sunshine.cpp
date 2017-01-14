#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class EelAndRabbit
{
	public:
	int n;
	vector<int> x;
	int getmax(vector<int> l,vector<int> t)
	{
		n=t.size();
		//The rabbits' positions must be exactly at ends of segments
		for(int i=0;i<n;i++)
		{
			l[i]+=t[i];
			x.push_back(l[i]);
			x.push_back(t[i]);
		}
		int ans=0;
		//Try all possible positions and update the answer.
		for(int i=0;i<x.size();i++)
			for(int j=0;j<x.size();j++)
			{
				int cnt=0;
				for(int k=0;k<n;k++)
					if((t[k]<=x[i]&&x[i]<=l[k])||(t[k]<=x[j]&&x[j]<=l[k]))
						cnt++;
				ans=max(ans,cnt);
			}
		return ans;
	}
};

