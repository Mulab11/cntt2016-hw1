#include<iostream>
#include<cstdio>
#include<vector>
#define N 2510
#define ll long long
using namespace std;
string a;
int n,f[N][N],g[N][N];
ll ans;
struct LittleElephantAndRGB
{
ll getNumber(vector<string> w,int m)
{
	a=" ";
	for(int i=0;i<w.size();i++) a+=w[i];
	n=a.size()-1;
	for(int i=1;i<=n;i++)
	{
		int q=0,now=0,maxn=0;
		bool flag=true;
		for(int j=i;j;j--)
		{
			if(a[j]=='G')
			{
				now++;
				maxn=max(maxn,now);
				if(flag) q++;
			}
			else now=0,flag=false;
			if(maxn>=m) f[i][m]++;
			else f[i][q]++;
		}
		int x=0;
		for(int j=m;j;j--) x+=f[i][j],g[i][j]=g[i-1][j]+x;
	}
	for(int i=1;i<=n;i++)
	{
		int q=0,now=0,maxn=0;
		bool flag=true;
		for(int j=i;j<=n;j++)
		{
			if(a[j]=='G')
			{
				now++;
				maxn=max(maxn,now);
				if(flag) q++;
			}
			else now=0,flag=false;
			if(maxn>=m) ans+=i*(i-1)/2;
			else ans+=g[i-1][m-q];
		}
	}
	return ans;
}
};