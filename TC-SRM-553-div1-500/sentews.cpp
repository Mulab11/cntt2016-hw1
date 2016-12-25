#include<vector>
#include<algorithm>
#include<cstring>
#include<string>
#include<cstdio>
#include<iostream>
using namespace std;
int f[55][55]={};int codeforces=1000000007;
int g[55][55]={};int n,m;int ans=0;
int l[55]={},r[55]={};
void count()//利用dp统计个数，但要注意初值
{
	for(int i=0;i<n;i++)
		l[i]=0,r[i]=m;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			if(f[i][j]==1)
				l[i]=j+1;
	for(int i=0;i<n;i++)
		for(int j=m-1;j>=0;j--)
			if(f[i][j]==-1)
				r[i]=j;
	for(int i=0;i<=n;i++)
		for(int j=0;j<=m;j++)
			g[i][j]=0;
	for(int i=l[0];i<=r[0];i++)
		g[0][i]=1;
	r[n]=l[n]=0;
	for(int i=1;i<=n;i++)
		for(int j=l[i];j<=r[i];j++)
			for(int k=j;k<=m;k++)
				g[i][j]=(g[i][j]+g[i-1][k])%codeforces;
	ans=(ans+g[n][0])%codeforces;
}
void rrr()
{
	count();
	for(int i=0,j=n-1;i<j;i++,j--)//垂直翻转
		for(int k=0;k<m;k++)
			swap(f[i][k],f[j][k]);
	count();
}
void vvv(int oo)//暴力判断是否成立
{
	bool flag=1;
	for(int j=0;j<n;j++)
		for(int k=0;k<m;k++)
			if(f[j][k]+g[j][k]==0)
				flag=0;
	if(flag)
		ans-=oo;
}
void ppp(int s)
{
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			g[i][j]=s;
	for(int i=0;i<m;i++)
		g[0][i]=-s;
	for(int i=1;i<n;i++)
	{
		vvv(1);
		for(int j=0;j<m;j++)
			g[i][j]=-s;
	}
}
void ppp2(int s)
{
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			g[i][j]=s;
	for(int i=0;i<n;i++)
		g[i][0]=-s;
	for(int i=1;i<m;i++)
	{
		vvv(1);
		for(int j=0;j<n;j++)
			g[j][i]=-s;
	}
}
void ppp3(int s)
{
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			g[i][j]=s;
	vvv(3);
}
class TwoConvexShapes
{  
	public:  
	int countWays(vector <string> grid)
	{  
		n=grid.size();
		m=grid[0].size();
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(grid[i][j]=='W')
					f[i][j]=1;
				else if(grid[i][j]=='B')
					f[i][j]=-1;
		rrr();//统计白色单调不减和单调不增
		for(int i=0;i<n;i++)//黑白互换，不影响结果
			for(int j=0;j<m;j++)
				f[i][j]=-f[i][j];
		rrr();//再次统计白色单调不减和单调不增的情况，就是黑色单调减情况
		ppp(1);//黑白上下分开，每成立一个说明多统计一个
		ppp(-1);
		ppp2(1);//黑白左右分开，每成立一个说明多统计一个
		ppp2(-1);
		ppp3(1);//全黑或者全白，成立说明多统计三个
		ppp3(-1);
		ans+=codeforces;
		ans%=codeforces;
		return ans;
	}
};
