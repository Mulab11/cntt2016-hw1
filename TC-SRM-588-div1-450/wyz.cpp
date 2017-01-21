// BEGIN CUT HERE

// END CUT HERE
#line 5 "KeyDungeonDiv1.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=14;
const int maxm=6666;

inline int lowbit(int x){return x&-x;}

int bin[maxn],bl[maxm];

int sumk[maxm],n,needR[maxn];
int needG[maxn],getR[maxn],getG[maxn],getW[maxn];

int dp[maxm][144];
bool vis[maxm];
void solve(int mask){
	if (vis[mask])return;
	vis[mask]=1;
	if (sumk[mask]<0) return;
	for (int j=mask,k=lowbit(j);j;k=lowbit(j-=k)){
		int to=mask^k,u=bl[k];
		if (sumk[to]<needR[u]+needG[u]) continue;
		int p=130;
		while (dp[to][p]<0&&p>=0) --p;
		for (int i=p+getR[u];i>=getR[u];--i){
			if (p-needR[u]+getR[u]>i) --p;
			while (p>=0&&dp[to][p]<0) --p;
			for (int v=i-getR[u];v<=p;++v)if (dp[to][v]>=0&&dp[to][v]+v>=needR[u]&&sumk[to]-v>=needG[u])
				dp[mask][i]=max(dp[mask][i],min(sumk[mask]-i-getG[u],dp[to][v]+v+getR[u]-i-needR[u]+getW[u]));
		}
	}
}

class KeyDungeonDiv1 {
	public:
	int maxKeys(vector <int> doorR, vector <int> doorG, vector <int> roomR, vector <int> roomG, vector <int> roomW, vector <int> keys){
//---prepare---begin
		n=doorR.size();
		for (int i=0;i<=n;++i) bl[bin[i]=1<<i]=i;
		for (int i=0;i<n;++i) needR[i]=doorR[i],needG[i]=doorG[i],getR[i]=roomR[i],getG[i]=roomG[i],getW[i]=roomW[i];
		for (int i=0;i<bin[n];++i){
			sumk[i]=keys[0]+keys[1]+keys[2];
			for (int j=i,k=lowbit(j);j;k=lowbit(j-=k))
				sumk[i]+=roomR[bl[k]]+roomG[bl[k]]+roomW[bl[k]]-doorR[bl[k]]-doorG[bl[k]];
		}
//---prepare---end
		memset(vis,0,sizeof(vis));
		memset(dp,-1,sizeof(dp));
		vis[0]=1;
		dp[0][keys[0]]=keys[2];
		for (int i=1;i<bin[n];++i) solve(i);
		int ret=sumk[0];
		for (int i=1;i<bin[n];++i)
			for (int j=0;j<=130;++j)if (dp[i][j]>=0){
				ret=max(ret,sumk[i]);
//				printf("%d %d %d\n",i,j,dp[i][j]);
				break;
			}
		return ret;
	}
};
