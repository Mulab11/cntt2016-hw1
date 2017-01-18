#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
struct IncrementAndDoubling
{
int getMin(vector<int> a)
{
	int ans=0,maxn=0;
	for(int i=0;i<a.size();i++)
	{
		int s=0,x=a[i];
		while(x)
		{
			if(x&1) ans++,x--;
			else s++,x/=2;
		}
		maxn=max(maxn,s);
	}
	return ans+maxn;
}
};