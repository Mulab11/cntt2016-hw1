#include<bits/stdc++.h>
using namespace std;
int n,t[55],i=1,s;
class TomekPhone//贪心
{
	public:
		int minKeystrokes(vector<int> a,vector<int> b)
		{
			for(auto x:b)while(x)t[x--]++;
			for(n=a.size(),sort(a.begin(),a.end());i<55&&n;i++)while(t[i]--&&n)s+=a[--n]*i;
			return n?-1:s;
		}
};
