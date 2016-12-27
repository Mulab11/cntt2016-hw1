#include<bits/stdc++.h>
using namespace std;
int n,m,P=1e9+9;
map<int,int> S[11];
vector<string> f;
vector<int> a,e;
int dfs(vector<int> x,int k)//记忆化搜索
{
	if(!k)return 1;
	int H=0,i=0,j;
	for(;i<m;i++)H=(233ll*H+x[i])%P;
	if(S[k].find(H)!=S[k].end())return S[k][H];
	for(i=0;i<m;i++)
	{
		vector<int> y=x;
		for(j=0;j<m;j++)if(y[j]=max(y[j],a[k-1]-abs(i-j)),(a[k-1]-abs(i-j)>x[j])^(f[k-1][j]=='X'))goto E;
		(S[k][H]+=dfs(y,k-1))%=P;E:;
	}
	return S[k][H];
}
class Mountains
{
	public:
		int countPlacements(vector<int> A,vector<string> F){return a=A,f=F,n=a.size(),e.resize(m=f[0].size()),dfs(e,n);}
};
