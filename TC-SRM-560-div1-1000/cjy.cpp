#include<bits/stdc++.h>
using namespace std;
int e[13][13],i,j,t,n,N,f[13];
double re,v[13],E,F;
vector<int> l,r;
string S;
void dfs(int k)
{
	if(k<n)v[k]=l[k],dfs(k+1),v[k]=r[k],dfs(k+1),f[k]=1,dfs(k+1),f[k]=0;else
	{
		for(i=t=E=F=0;i<n;E+=v[i++])if(f[i])for(t++,v[i]=j=0;j<n;j++)v[i]+=!f[j]*v[j]*e[i][j];
		if(!t&&E>N)return;
		for(i=0;i<n;i++)if(f[i])if(v[i]+=(N-E)/t,v[i]<l[i]||v[i]>r[i])return;
		for(i=0;i<n;i++)for(j=i+1;j<n;j++)F+=e[i][j]*v[i]*v[j];re=max(re,F);
	}
}
class BoundedOptimization
{
	public:
		double maxValue(vector<string> _,vector<int> L,vector<int> R,int s)
		{
			for(auto x:_)S+=x;
			for(N=s,n=L.size(),l=L,r=R;i<S.size();i+=3)e[S[i+1]-97][S[i]-97]=e[S[i]-97][S[i+1]-97]=1;
			return dfs(0),re;
		}
};
