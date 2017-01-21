// BEGIN CUT HERE

// END CUT HERE
#line 5 "LittleElephantAndPermutationDiv1.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=52;
const int P=1000000007;

int n;
int dp[maxn][maxn][2000];

class LittleElephantAndPermutationDiv1{
	public:
	int getNumber(int N, int K){
		n=N;
		memset(dp,0,sizeof(dp));
		dp[0][0][0]=1;
		for (int i=0;i<n;++i){
			for (int j=0;j<=i;++j)
				for (int k=1950;k>=0;--k)if (dp[i][j][k]){
					(dp[i+1][j+2][k+(i+1)*2]+=(ll)dp[i][j][k]*(i-j)*(i-j)%P)%=P;
					(dp[i+1][j+1][k+(i+1)]+=(ll)dp[i][j][k]*(n-i*2+j)*(i*2-j*2+1)%P)%=P;
					(dp[i+1][j][k]+=(ll)dp[i][j][k]*(n-i*2+j)*(n-i*2+j-1)%P)%=P;
				}
		}
		int ret=0;
		for (int i=K;i<2000;++i) (ret+=dp[n][n][i])%=P;
		return ret;
	}
};

//this is for test
/*
int main(){
	LittleElephantAndPermutationDiv1 test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
