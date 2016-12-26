#include <bits/stdc++.h>

#define rep(x,a,b) for (int x=a;x<=(int)b;x++)
#define drp(x,a,b) for (int x=a;x>=(int)b;x--)
#define cross(x,a) for (int x=hd[a];~x;x=nx[x])
#define ll long long
#define inf (1<<29)
#define PII pair<int,int>
#define PDD pair<double,double>
#define mk(a,b) make_pair(a,b)
#define fs first
#define sc second
#define pb push_back
#define VI vector<int>
#define VS vector<string>

using namespace std;

/*
搜
每条不存在的边都是一个限制，初始化答案为全集，然后决策每条不存在的边
一个状态有两分支当且仅当两个端点都在答案中，复杂度即为O(2^(n/3)n^2)
*/

const int maxn=55;
ll mp[maxn];
const int dd=262143;
int n32,d[maxn],ans=-1,n,val[maxn],sum,no[270000];

void dfs(int nw,int rem,int sum,ll ava){
	if (nw==-1) return void(ans=sum);
	if ((ava>>nw)&1) dfs(nw-1,rem-1,sum,ava&mp[nw]),ava^=(1ll<<nw);
	int cnt=no[ava&dd]+no[ava>>18&dd]+no[ava>>36&dd];
	if (rem>cnt) return;
	sum-=val[nw];
	if (sum<ans) return;
	dfs(nw-1,rem,sum,ava);
}
bool cmp(const int &a,const int &b){return d[a]<n32?d[b]<n32?val[a]<val[b]:0:d[b]<n32?1:val[a]<val[b];}
int idx[maxn];
int lowbit(int x){return x&-x;}
struct MagicMolecule{
	int maxMagicPower(VI pw,VS mpp){
		n=pw.size();
		rep(i,0,n-1) val[i]=pw[i],idx[i]=i;
		rep(i,0,n-1) rep(j,0,n-1) if (mpp[i][j]=='Y') d[i]++;
		rep(i,0,n-1) d[i]++;
		n32=(n*2+2)/3,sort(idx,idx+n,cmp);
		rep(i,0,n-1) val[i]=pw[idx[i]];
		while (n>0&&d[idx[n-1]]<n32) n--;
		if (n<n32) return -1;
		rep(i,1,dd) no[i]=no[i-lowbit(i)]+1;
		rep(i,0,n-1) sum+=pw[idx[i]];
		rep(i,0,n-1) rep(j,0,n-1) if (mpp[idx[i]][idx[j]]=='Y') mp[i]|=1ll<<j;
		dfs(n-1,n32,sum,(1ll<<n)-1);
		return ans;
	}
};
