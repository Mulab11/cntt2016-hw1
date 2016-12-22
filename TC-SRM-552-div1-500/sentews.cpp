#include<algorithm>
#include<cstdio>
#include<string>
#include<vector>
#include<iostream>
using namespace std;
int a[33][33]={},b[33][33]={};
int n,m,p;int ans=-1;char flowers[33][33]={};
int f[33][33]={};int g1[33][2111]={};
int g2[33][2111]={};
int get1(int i,int j,int k,int l)
{return a[k][l]-a[i][l]-a[k][j]+a[i][j];}
int get2(int i,int j,int k,int l)
{return b[k][l]-b[i][l]-b[k][j]+b[i][j];}
void clear()
{
	for(int i=0;i<=32;i++)
		for(int j=0;j<=32;j++)
			f[i][j]=a[i][j]=b[i][j]=0;
	for(int i=0;i<32;i++)
		for(int j=0;j<=2000;j++)
			g1[i][j]=g2[i][j]=-111110;
}
void rrr()
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			a[i][j]=a[i-1][j]+a[i][j-1]-a[i-1][j-1]+f[i][j],b[i][j]=b[i-1][j]+b[i][j-1]-b[i-1][j-1]+abs(f[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=i;k<=n;k++)
				for(int l=j;l<=m;l++)
				{
					int nn=get1(i-1,j-1,k,l);//权值得和
					int mm=get2(i-1,j-1,k,l);//总和
					g1[k][nn+1000]=max(g1[k][nn+1000],mm);
					g2[i][nn+1000]=max(g2[i][nn+1000],mm);
				}
	for(int i=2;i<=n;i++)
		for(int j=0;j<=2000;j++)
			if(g1[i][j]<g1[i-1][j])
				g1[i][j]=g1[i-1][j];
	for(int i=n-1;i>0;i--)
		for(int j=0;j<=2000;j++)
			if(g2[i][j]<g2[i+1][j])
				g2[i][j]=g2[i+1][j];
	for(int k=1;k<n;k++)
		for(int i=100;i<=1900;i++)
			for(int j=100;j<=1900;j++)
				if(ans<g1[k][i]+g2[k+1][j]&&abs(i+j-2000)<=p)
					ans=g1[k][i]+g2[k+1][j];
}
class FoxAndFlowerShopDivOne
{
	public:
	int theMaxFlowers(vector<string> flowers, int maxDiff)
	{
		n=flowers.size(),m=flowers[0].size();p=maxDiff;clear();
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(flowers[i][j]=='L')
					f[i+1][j+1]=1;
				else if(flowers[i][j]=='P')
					f[i+1][j+1]=-1;
		rrr();
		m=flowers.size(),n=flowers[0].size();clear();
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(flowers[j][i]=='L')
					f[i+1][j+1]=1;
				else if(flowers[j][i]=='P')
					f[i+1][j+1]=-1;
		rrr();
		return ans;
	}
};
