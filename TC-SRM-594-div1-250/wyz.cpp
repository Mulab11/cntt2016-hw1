// BEGIN CUT HERE

// END CUT HERE
#line 5 "AstronomicalRecords.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
#define N 55
const int maxa=1e9;

class AstronomicalRecords{
	int a[N],b[N],n,m;
	int dp[N][N];
	int doit(){
		dp[0][0]=0;
		for (int i=1;i<=n;++i) dp[i][0]=i;
		for (int j=1;j<=m;++j) dp[0][j]=j;
		for (int i=1;i<=n;++i)
			for (int j=1;j<=m;++j)
				dp[i][j]=a[i]==b[j]?dp[i-1][j-1]+1:(min(dp[i-1][j],dp[i][j-1])+1);
		return dp[n][m];
	}
	public:
	int minimalPlanets(vector <int> A, vector <int> B){
		int ret=A.size()+B.size();
		n=A.size();
		for (int i=0;i<n;++i) a[i+1]=A[i];
		for (int i=1;i<=n;++i)
			for (int j=0;j<B.size();++j){
				m=0;
				int cnt=0;
				for (int k=0;k<B.size();++k){
					ll now=(ll)B[k]*a[i];
					if (now%B[j]||now/B[j]>maxa) ++cnt;
					else b[++m]=now/B[j];
				}
				ret=min(ret,cnt+doit());
			}
		return ret;
	}
};

//this is for test
/*
int main(){
	AstronomicalRecords test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
