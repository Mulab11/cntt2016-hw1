// BEGIN CUT HERE

// END CUT HERE
#line 5 "StringPath.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxm=260;
#define P 1000000009
int bin[9];

class StringPath{
	int dp[maxm][maxm],f[maxm][maxm];
	public:
	int countBoards(int n, int m, string A, string B){
		for (int i=0;i<9;++i) bin[i]=1<<i;
		if (A[0]!=B[0]||A[n+m-1]!=B[n+m-1]) return 0;
		memset(dp,0,sizeof(dp));dp[1][1]=1;
		for (int i=0;i<n;++i)for (int j=i==0;j<m;++j){
			memset(f,0,sizeof(f));
			for (int msk0=1;msk0<bin[m];++msk0)for (int msk1=1;msk1<bin[m];++msk1)if (dp[msk0][msk1]){
//				printf("%d %d  %d %d  %d\n",i,j,msk0,msk1,dp[msk0][msk1]);
				bool flag0=(msk0&bin[m-1])||((msk0&1)&&j),flag1=(msk1&bin[m-1])||((msk1&1)&&j);
				ll cnt=26;
				if (flag0&&flag1&&A[i+j]==B[i+j])
					(f[1^(msk0<<1)&(~bin[m])][1^(msk1<<1)&(~bin[m])]+=dp[msk0][msk1])%=P,--cnt;
				else{
					if (flag0) (f[1^(msk0<<1)&(~bin[m])][(msk1<<1)&(~bin[m])]+=dp[msk0][msk1])%=P,--cnt;
					if (flag1) (f[(msk0<<1)&(~bin[m])][1^(msk1<<1)&(~bin[m])]+=dp[msk0][msk1])%=P,--cnt;
				}
				(f[(msk0<<1)&(~bin[m])][(msk1<<1)&(~bin[m])]+=cnt*dp[msk0][msk1]%P)%=P;
			}
			memcpy(dp,f,sizeof(f));
		}
		int ret=0;
		for (int i=0;i<bin[m-1];++i)
			for (int j=0;j<bin[m-1];++j)
				(ret+=dp[i<<1^1][j<<1^1])%=P;
		return ret;
	}
};

//this is for test
/*
int main(){
	StringPath test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
