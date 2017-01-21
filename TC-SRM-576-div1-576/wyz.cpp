// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheExperiment.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

class TheExperiment{
	#define N 305
	#define P 1000000009
	int a[N],n;
	int dp[N][N][2];
	int s[N][N];
	public:
	int countPlacements(vector <string> intensity, int M, int L, int A, int B){
		n=0;
		for (int i=0;i<intensity.size();++i)
			for (int j=0;j<intensity[i].size();++j)
				a[++n]=intensity[i][j]-48;
		memset(dp,0,sizeof(dp));
		memset(s,0,sizeof(s));
		for (int i=0;i<=n;++i) s[i][0]=1;
		dp[0][0][0]=1;
		for (int i=1;i<=n;++i)for (int j=1;j<=M;++j){
			int sum=0;
			for (int k=0;k<L;++k){
				if (i-k==0) break;
				sum+=a[i-k];
				if (sum<A) continue;
				if (sum>B) break;
//				if (k==L-1) printf("%d\n",i);
				(dp[i][j][1]+=dp[i-k-1][j-1][1])%=P;
				(dp[i][j][k==L-1]+=dp[i-k-1][j-1][0])%=P;
				if (i-k>1) (dp[i][j][k==L-1]+=s[i-k-2][j-1])%=P;
			}
			s[i][j]=(s[i-1][j]+dp[i][j][1])%P;
		}
		
		return s[n][M];
	}
};
