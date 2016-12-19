#include<bits/stdc++.h>
using namespace std;
int f[65536][16],t[65536],d[55][55],l[16],r[16],c[16],s,i,j,k,n;
void get(string s,int&a,int&b,int&c)
{
	int i=0,n=s.size();
	while(s[i]!=' ')a=a*10+s[i]-48,i++;
	while(s[++i]!=' ')b=b*10+s[i]-48;
	while(++i<n)c=c*10+s[i]-48;
}
class TravellingPurchasingMan
{
	public:
		int maxStores(int m,vector<string> a,vector<string> e)
		{
			for(memset(d,9,sizeof(d)),memset(f,9,sizeof(f)),n=a.size();i<n;i++)get(a[i],l[i],r[i],c[i]),d[i][i]=0;
			for(auto x : e)get(x,i=0,j=0,k=0),d[i][j]=d[j][i]=k;
			for(k=0;k<m;k++)for(i=0;i<m;i++)for(j=0;j<m;j++)d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
			for(i=0;i<(1<<n);i++)for(t[i]=t[i/2]+i%2,j=0;j<n;j++)if(i>>j&1)
			{
				if(i==(1<<j))f[i][j]=d[j][m-1];
				for(k=0;k<n;k++)if((i>>k&1)&&k!=j)f[i][j]=min(f[i][j],f[i-(1<<j)][k]+d[j][k]);
				if((f[i][j]=max(f[i][j],l[j]))<=r[j])f[i][j]+=c[j],s=max(s,t[i]);else f[i][j]=1<<30;
			}
			return s;
		}
};
