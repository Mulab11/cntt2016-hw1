#include<bits/stdc++.h>
using namespace std;
int S,n,m,i,j,l[55],r[55],f[55][55],t,P=1e9+7; vector<string> a;
void G()//讨论，DP
{
	for(i=0;i<=m;i++)f[0][i]=1;
	for(i=1;i<=n;i++)for(j=0;j<=m;j++)if(f[i][j]=j?f[i][j-1]:0,l[i-1]<j&&r[i-1]>=j)f[i][j]=(f[i][j]+f[i-1][j])%P;S=(S+f[n][m])%P;
}
void W()
{
	for(t=i=0;i<n;i++)for(j=0,l[i]=-1,r[i]=m;j<m;j++)
	{
		if(a[i][j]=='B')l[i]=j;
		if(a[i][j]=='W'&&j<r[i])t=1,r[i]=j;
	}
	for(S+=!t,j=-1;j<n;S-=!t,j++)
	{
		for(i=t=0;i<=j;i++)t|=r[i]<m;
		for(i=j+1;i<n;i++)t|=l[i]>=0;
	}
	for(j=-1;j<=m;S-=!t,j++)for(i=t=0;i<n;i++)t|=l[i]>j||r[i]<=j;
	for(G(),i=0;i<n/2;i++)swap(l[i],l[n-i-1]),swap(r[i],r[n-i-1]);G();
}
class TwoConvexShapes
{
	public:
		int countWays(vector<string> A)
		{
			for(n=A.size(),m=A[0].size(),a=A,W(),i=0;i<n;i++)for(j=0;j<m;j++)if(a[i][j]^'?')a[i][j]='B'+'W'-a[i][j];
			return W(),S;
		}
};
