#include<bits/stdc++.h>
using namespace std;
long long b[50];
int a[50],n,s=-1,d[50],i,j,t,T;
void dfs(int k,long long x)
{
	for(i=j=t=0;i<n;i++)if(x>>i&1)t++,j+=a[i];
	if(j<=s||t<n-n/3)return;
	if(k==n){s=j;return;}
	if(x>>k&1)dfs(k+1,x&b[k]);else dfs(k+1,x);
}
class MagicMolecule//随机化
{
	public:
		int maxMagicPower(vector<int> A,vector<string> E)
		{
			REP:;
			for(n=A.size();i<n;i++)d[i]=i;
			for(random_shuffle(d,d+n),i=0;i<n;i++)for(a[i]=A[d[i]],b[i]=j=0;j<n;j++)if(j==i||E[d[i]][d[j]]=='Y')b[i]|=1ll<<j;
			if(dfs(0,(1ll<<n)-1),++T<=100000)goto REP;
			return s;
		}
};
