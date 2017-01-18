#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define M 310
using namespace std;
struct WolfInZooDivOne
{
	int l[M],r[M],p[M],m;
	int f[M][M],pre[M][M];
	static const int mod=1e9+7;
	int count(int N, vector <string> L, vector <string> R)
	{
		string T="";
		int i,j,x,y,now;
		for(i=0;i<L.size();i++)
		T+=L[i];
		T+=" ";
		now=0;
		for(i=0;i<T.size();i++)
		{
			if(T[i]==' ') m++,l[m]=now+1,now=0;
			else now=now*10+T[i]-48;
		}
		T="";
		for(i=0;i<R.size();i++)
		T+=R[i];
		T+=" ";
		now=0;m=0;
		for(i=0;i<T.size();i++)
		{
			if(T[i]==' ') m++,r[m]=now+1,now=0;
			else now=now*10+T[i]-48;
		}
		for(i=1;i<=N;i++)
		{
			p[i]=707185547;
			for(j=1;j<=m;j++)
			if(i<=r[j])
			p[i]=min(p[i],l[j]);
		}
		for(i=1;i<=N;i++)
		{
			f[i][0]=1;pre[i][0]=1;
			for(j=1;j<i;j++)
			{
				f[i][j]=pre[j][min(j-1,p[i]-1)];
				(pre[i][j]=pre[i][j-1]+f[i][j])%=mod;
			}
		}
		int ans=1;
		for(i=1;i<=N;i++)
		(ans+=pre[i][i-1])%=mod;
		return ans;
	}
};