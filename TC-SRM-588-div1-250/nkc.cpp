#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 51
using namespace std;
struct ppp
{int t,v;}b[N];
bool cmp(ppp x,ppp y)
{return x.v<y.v;}
struct GUMIAndSongsDiv1
{
	int f[N][N];
	int maxSongs(vector <int> duration, vector <int> tone, int T)
	{
		int n=tone.size();
		int i,j,k;
		for(i=0;i<n;i++)
		b[i+1]=(ppp)
		{duration[i],tone[i]};
		sort(b+1,b+n+1,cmp);
		int ans=0;
		for(i=1;i<=n;i++)
		{
			f[i][0]=0;
			f[i][1]=b[i].t;
			if(f[i][1]<=T) ans=max(ans,1);
			for(j=2;j<=i;j++)
			{
				f[i][j]=707185547;
				for(k=j-1;k<i;k++)
				f[i][j]=min(f[i][j],f[k][j-1]+b[i].v-b[k].v+b[i].t);
				if(f[i][j]<=T) ans=max(ans,j);
			}
		}
		return ans;
	}
};