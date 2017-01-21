// BEGIN CUT HERE

// END CUT HERE
#line 5 "Excavations.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=55;

class Excavations{
	pair<int,int> tmp[maxn];
	ll c[maxn][maxn];
	int n;
	ll dp[maxn][maxn];
	int cnt[maxn][maxn],m;
	bool fnd[maxn];
	public:
	long long count(vector <int> kind, vector <int> depth, vector <int> found, int K){
		n=kind.size();
		c[0][0]=1;
		for (int i=1;i<=n;++i){
			c[i][0]=1;
			for (int j=1;j<=n;++j) c[i][j]=c[i-1][j]+c[i-1][j-1];
		}
		memset(cnt,0,sizeof(cnt));
		m=0;
		for (int i=0;i<n;++i) tmp[i]=make_pair(depth[i],kind[i]),m=max(m,kind[i]);
		sort(tmp,tmp+n);
		int x=0;
		for (int i=0;i<n;++i){
			if (i==0||tmp[i].first!=tmp[i-1].first) ++x;
			++cnt[tmp[i].second][x];
		}
		n=x;
		for (int i=1;i<=m;++i)
			for (int j=1;j<=n;++j) cnt[i][j]+=cnt[i][j-1];
		memset(fnd,0,sizeof(fnd));
		for (int i=0;i<found.size();++i) fnd[found[i]]=1;

		ll ret=0;
		for (int gap=1;gap<n+1;++gap){
			memset(dp,0,sizeof(dp));
			if (gap<n){
				int num=0,t=0;
				for (int i=1;i<=m;++i){
					num+=cnt[i][n]-cnt[i][gap];
					if (!fnd[i]) t+=cnt[i][gap+1]-cnt[i][gap],num-=cnt[i][gap+1]-cnt[i][gap];
				}
				if (!t) continue;
				for (int i=1;i<=K&&i<=num+t;++i)
					for (int j=1;j<=i&&j<=t;++j)
						dp[0][i]+=c[t][j]*c[num][i-j];
			}
			else dp[0][0]=1;
			for (int i=1;i<=m;++i)if (fnd[i])
				for (int j=1;j<=K;++j)
					for (int k=1;k<=cnt[i][gap]&&k<=j;++k)
						dp[i][j]+=dp[i-1][j-k]*c[cnt[i][gap]][k];
			else for (int j=0;j<=K;++j) dp[i][j]=dp[i-1][j];
			ret+=dp[m][K];
		}
		return ret;
	}
};
