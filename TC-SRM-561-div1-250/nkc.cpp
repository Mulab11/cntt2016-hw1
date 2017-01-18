#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 51
using namespace std;
int L[N],M[N];
bool cmp(int x,int y)
{return x>y;}
int cl,cm;
int a[16];
int ans=707185547;
int n,m;
void dfs(int x,int ll,int mm,int now,int rel,int rem)
{
	if(now>=ans) return;
	if(x==m+1) 
	{ans=now;return;}
	if(rel>=a[x])//用L型号 
	{
		if(ll<=cl)
		dfs(x+1,ll+1,mm,now+max(0,a[x]-L[ll]),rel-a[x],rem);
		else
		dfs(x+1,ll,mm,now+a[x],rel-a[x],rem);
	}
	if(rem>=a[x])//用M型号 
	{
		if(mm<=cm)
		dfs(x+1,ll,mm+1,now+max(0,a[x]-M[mm]),rel,rem-a[x]);
		else
		dfs(x+1,ll,mm,now+a[x],rel,rem-a[x]);
	}
}
struct ICPCBalloons
{
	int minRepaintings(vector <int> balloonCount, string balloonSize, vector <int> maxAccepted)
	{
		m=maxAccepted.size(),n=balloonCount.size();
		int i,j,totl=0,totm=0;
		for(i=0;i<n;i++)
		{
			if(balloonSize[i]=='L') cl++,L[cl]=balloonCount[i],totl+=L[cl];
			else cm++,M[cm]=balloonCount[i],totm+=M[cm];
		}
		for(i=0;i<m;i++)
		a[i+1]=maxAccepted[i];
		sort(L+1,L+cl+1,cmp);
		sort(M+1,M+cm+1,cmp);
		sort(a+1,a+m+1,cmp);
		dfs(1,1,1,0,totl,totm);//暴力枚举每种气球的大小 
		if(ans==707185547) return -1;
		return ans;
	}
};