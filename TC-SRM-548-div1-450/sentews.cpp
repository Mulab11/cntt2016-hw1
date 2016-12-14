#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
int f[66][3222]={};
int g[55]={},n;
int a[55]={},b[55]={};int x;
int num=0,cnt=0;
class KingdomAndDice
{
    public:
    double newFairness(vector<int> firstDie, vector<int> secondDie, int X)
	{
    	x=X;
		n=firstDie.size();
		for(int i=0;i<n;i++)
			a[i]=firstDie[i],b[i]=secondDie[i];
		sort(a,a+n);
		sort(b,b+n);
		for(int i=0;i<n;i++)
			if(a[i]==0)
				num++;
		for(int i=num;i<n;i++)
			for(int j=0;j<n;j++)
				if(a[i]>b[j])
					cnt++;
		b[n]=x+1;
		for(int i=1;i<=n;i++)
		{
			g[i]=b[i]-b[i-1]-1;
			for(int j=0;j<n;j++)
				if(a[j]>b[i-1]&&a[j]<b[i])
					g[i]--;
		}
		for(int i=1;i<=n*n;i++)
			f[0][i]=222222222;
		for(int i=1;i<=n;i++)
			for(int j=0;j<=n*n;j++)
			{
				f[i][j]=222222222;
				for(int k=0;k<=g[i]&&k*i<=j;k++)
					f[i][j]=min(f[i][j],f[i-1][j-k*i]+k);
			}
		double ans=1111;
		for(int i=cnt;i<=n*n;i++)
		{
			if(f[n][i-cnt]<=num&&fabs(1.0*i/n/n-0.5)<fabs(ans-0.5)-1e-10)
				ans=1.0*i/n/n;
		}
		return ans;
    }
};
