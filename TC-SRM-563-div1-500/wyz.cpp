// BEGIN CUT HERE

// END CUT HERE
#line 5 "SpellCards.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

inline void Max(int &x,int y){if (y>x) x=y;}

const int maxn=53;

class SpellCards{
	int a[maxn],dam[maxn],n;
	int dp[maxn][maxn];
	int work(){
		memset(dp,192,sizeof(dp));
		dp[0][0]=0;
		for (int i=0;i<n;++i)for (int j=0;j<maxn;++j){
			Max(dp[i+1][max(j-1,0)],dp[i][j]);
			if (j+a[i]<maxn) Max(dp[i+1][j+a[i]],dp[i][j]+dam[i]);
		}
		return dp[n][0];
	}
	public:
	int maxDamage(vector <int> level, vector <int> damage){
		n=level.size();
		for (int i=0;i<n;++i) a[i]=level[i]-1,dam[i]=damage[i];
		int ret=0;
		for (int i0=0;i0<n;++i0){
			Max(ret,work());
			for (int i=0;i<n-1;++i) swap(a[i],a[i+1]),swap(dam[i],dam[i+1]);
		}
		return ret;
	}
};
