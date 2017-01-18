#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 51
using namespace std;
struct TheTree
{
	int maximumDiameter(vector <int> cnt)
	{
		int n=cnt.size();
		int i,j,t=n-1,ans=0;
		for(i=n-1;i>=-1;i--)//计算深度i为根的答案 
		{
			ans=max(ans,n-1-i+t-i);//一叉到底，另一叉到第一个只有一个的点上方 
			if(i!=-1&&cnt[i]==1) t=i-1;
		}
		return ans;
	}
};