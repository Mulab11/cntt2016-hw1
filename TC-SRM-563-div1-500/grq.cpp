#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

const int N=55;
int n,dp[N][N];

inline void upt(int &x,int y){if(x<y) x=y;}

class SpellCards{
public:
	int maxDamage(vector<int> level, vector<int> damage){
		n=level.size();
		memset(dp,0,sizeof(dp));
		for(int i=1;i<=n;i++)
			for(int j=0;j<=n;j++){
				dp[i][j]=dp[i-1][j];
				if(j>=level[i-1]) upt(dp[i][j],dp[i-1][j-level[i-1]]+damage[i-1]);
			}
		int ans=0;
		for(int i=0;i<=n;i++) upt(ans,dp[n][i]);
		return ans;
	}
};

