#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class StringPath{
	static const int mod=1000000009;
	long long dp[9][9][1<<8][1<<8];
	int tr0(int sta,int pos){
		if (sta&(1<<pos)) sta^=1<<pos;
		return sta;
	}
	int tr1(int sta,int pos){
		if (pos==0){
			return sta;
		}
		if (~sta&(1<<pos)){
			if (sta&(1<<(pos-1))) sta|=1<<pos;
		}
		return sta;
	}
	public:
	int countBoards(int n, int m, string A, string B){
		if (A[0]!=B[0]||A[n+m-2]!=B[n+m-2]){
			return 0;
		}
		memset(dp,0,sizeof(dp));
		dp[0][0][1][1]=1;
		for (int i=0;i<n;++i)
		for (int j=0;j<m;++j){
			if (i==n-1&&j==m-1) break;
			if (j==m-1)
				for (int a=0;a<(1<<m);++a)
				for (int b=0;b<(1<<m);++b){
					if (A[i+1]==B[i+1]){
						(dp[i+1][0][tr1(a,0)][tr1(b,0)]+=dp[i][j][a][b])%=mod;
						(dp[i+1][0][tr0(a,0)][tr0(b,0)]+=dp[i][j][a][b]*25)%=mod;
					}
					else{
						(dp[i+1][0][tr1(a,0)][tr0(b,0)]+=dp[i][j][a][b])%=mod;
						(dp[i+1][0][tr0(a,0)][tr1(b,0)]+=dp[i][j][a][b])%=mod;
						(dp[i+1][0][tr0(a,0)][tr0(b,0)]+=dp[i][j][a][b]*24)%=mod;
					}
				}
			else
				for (int a=0;a<(1<<m);++a)
				for (int b=0;b<(1<<m);++b){
					if (A[i+j+1]==B[i+j+1]){
						(dp[i][j+1][tr1(a,j+1)][tr1(b,j+1)]+=dp[i][j][a][b])%=mod;
						(dp[i][j+1][tr0(a,j+1)][tr0(b,j+1)]+=dp[i][j][a][b]*25)%=mod;
					}
					else{
						(dp[i][j+1][tr1(a,j+1)][tr0(b,j+1)]+=dp[i][j][a][b])%=mod;
						(dp[i][j+1][tr0(a,j+1)][tr1(b,j+1)]+=dp[i][j][a][b])%=mod;
						(dp[i][j+1][tr0(a,j+1)][tr0(b,j+1)]+=dp[i][j][a][b]*24)%=mod;
					}
				}
			}
			long long ret=0;
			int tmp=1<<(m-1);
			for (int a=0;a<(1<<m);++a)
			for (int b=0;b<(1<<m);++b) if (a&tmp) if (b&tmp) ret+=dp[n-1][m-1][a][b];
			return ret%mod;
	}
};
