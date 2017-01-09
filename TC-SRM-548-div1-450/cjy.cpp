#include<bits/stdc++.h>
using namespace std;
int n,m,i,t,f[55][2555],j,k,d;
double s=9,r;
class KingdomAndDice
{
	public:
		double newFairness(vector<int> a,vector<int> b,int R)
		{
			for(n=a.size(),sort(a.begin(),a.end()),sort(b.begin(),b.end());i<n;i++)m+=!a[i],t+=lower_bound(b.begin(),b.end(),a[i])-b.begin();
			for(memset(f,9,sizeof(f)),f[0][0]=0,b.push_back(R+1),i=1;i<=n;i++)
			{
				for(d=b[i]-b[i-1]-1,j=0;j<n;j++)d-=a[j]>b[i-1]&&a[j]<b[i];
				for(j=0;j<=n*n;j++)for(k=0;k<=d&&k*i<=j;k++)f[i][j]=min(f[i][j],f[i-1][j-k*i]+k);
			}
			for(i=0;i<=n*n;i++)if(r=1.*(i+t)/n/n,f[n][i]<=m&&abs(r-.5)<abs(s-.5)-1e-8)s=r;
			return s;
		}
};
