#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
struct SpellCards
{
	int f[51];
	int maxDamage(vector <int> level, vector <int> damage)
	{
		//直接转化成经典背包问题 
		int n=level.size();
		int i,j,x,y;
		for(i=0;i<n;i++)
		for(j=n;j>=level[i];j--)
		f[j]=max(f[j],f[j-level[i]]+damage[i]);
		//计算完毕返回结果即可 
		return f[n];
	}
};