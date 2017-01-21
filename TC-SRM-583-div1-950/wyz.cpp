// BEGIN CUT HERE

// END CUT HERE
#line 5 "RandomPaintingOnABoard.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=24;

class RandomPaintingOnABoard{
	double ans;
	void calc(int times,int u,int v,int f){
//		printf("%d %d %d %d\n",times,u,v,f);
		if (u) ans+=1.0*v/u*(f*2-1)*times;
	}
	int n,m,s,s1;
	int p[maxn][maxn];
	int a[maxn];
	int dp[1402][2];
	void DP(){
//		if (!s1) for (int i=1;i<=n;++i,puts(""))for (int j=1;j<=m;++j) printf("%d ",p[i][j]);
		memset(dp,0,sizeof(dp));
		dp[0][0]=1;
		for (int i=1;i<=m;++i)
			for (int j=s-s1;j>=a[i];--j){
				int tmp0=dp[j-a[i]][1],tmp1=dp[j-a[i]][0];
				dp[j][0]+=tmp0;
				dp[j][1]+=tmp1;
			}
	}
	void dfs(int u,int f){
		if (u>n){
			memset(a,0,sizeof(a));
			for (int i=1;i<=m;++i)
				for (int j=1;j<=n;++j)if (p[j][i]>0)
					a[i]+=p[j][i];
			DP();
			for (int j=s-s1;j>=0;--j)
				for (int k=0;k<2;++k)
					calc(dp[j][k],s1+j,s,k^f);
			return;
		}
		for (int k=0;k<2;++k){
			for (int i=1;i<=m;++i) s1-=(p[u][i]=-p[u][i]);
			dfs(u+1,f^1^k);
		}
	}
	public:
	double expectedSteps(vector <string> prob){
		n=prob.size();m=prob[0].size();
		s=0;
		for (int i=1;i<=n;++i)
			for (int j=1;j<=m;++j)
				s+=(((n<=m)?p[i][j]:p[j][i])=prob[i-1][j-1]-48);
//		printf("%d\n",s);
		if (n>m) swap(n,m);
		ans=0;
		s1=0;
		dfs(1,0);
		return ans;
	}
};
