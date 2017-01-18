#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring> 
#define N 60
#define M 600
using namespace std;
int n,x[N],y[N],f[M][M],sum[M][M];
bool vi[M][M];
int ask(int x,int y,int xx,int yy)
{
	return sum[xx][yy]-sum[x-1][yy]-sum[xx][y-1]+sum[x-1][y-1];
}
bool ch(int k)
{
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++) for(int j=x[i]-k;j<=x[i]+k;j+=2) for(int p=y[i]-k;p<=y[i]+k;p+=2) f[j][p]=1;
	for(int i=1;i<600;i++) for(int j=1;j<600;j++) sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+f[i][j];
	for(int i=k+1;i<600-k;i++)
	for(int j=k+1;j<600-k;j++)
	{
		if(ask(i-k,j-k,i+k,j+k)==(k+1)*(k+1))
		{
			if(!vi[i][j]) return false;
		} 
		else if(vi[i][j]) return false;
	}
	return true;
}
struct DrawingPointsDivOne
{
int maxSteps(vector<int> X,vector<int> Y)
{
	n=X.size();
	for(int i=0;i<n;i++)
	{
		x[i+1]=X[i]*2+300;
		y[i+1]=Y[i]*2+300;
		vi[x[i+1]][y[i+1]]=true;
	}
	int l=0,r=140;
	while(l<r)
	{
		int mid=(l+r+1)/2;
		if(ch(mid)) l=mid;
		else r=mid-1;
	}
	return l<140?l:-1;
}
};