// BEGIN CUT HERE

// END CUT HERE
#line 5 "FlippingBitsDiv1.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=305;
const int maxm=262333;

class FlippingBitsDiv1{
	int a[maxn],n,m,ans;

	int bin[20],m1;
	int dp[maxm];
	void DP(){
		for (int i=0;i<=m;++i) bin[i]=1<<i;
		m1=bin[m]-1;
		memset(dp,0,sizeof(dp));
		for (int i=0;i<=n/m;++i){
			for (int j=0;j<bin[m-1];++j){
				int cnt[2]={0,0};
				for (int k=i*m;k<i*m+m&&k<n;++k)
					++cnt[a[k]^(j>>(k-i*m)&1)];
				int tmp=min(dp[j]+cnt[1]+1,dp[j^m1]+cnt[0]);
				dp[j]=min(dp[j]+cnt[1],dp[j^m1]+cnt[0]+1);
				dp[j^m1]=tmp;
			}
		}
		for (int j=0;j<=m1;++j) ans=min(ans,dp[j]);
	}

	int tag[maxn],cnt[maxn][2];
	void dfs(int k,int now){
		if (k*m>=n){
			memset(cnt,0,sizeof(cnt));
			int tmp=0;
			for (int i=n-1;i>=0;--i){
				++cnt[i%m][tmp^a[i]];
				if (i%m==0) tmp^=tag[i/m];
			}
			for (int i=0;i<m;++i) now+=min(cnt[i][0],cnt[i][1]);
			ans=min(now,ans);
			return;
		}
		tag[k]=0;
		dfs(k+1,now);
		tag[k]=1;
		dfs(k+1,now+1);
	}
	public:
	int getmin(vector <string> S, int M){
		n=0;m=M;
		for (int i=0;i<S.size();++i)
			for (int j=0;j<S[i].size();++j)
				a[n++]=S[i][j]-48;
		ans=n;
		if (m*m<=n) DP();
		else dfs(1,0);
		return ans;
	}
};

//this is for test
/*
int main(){
	FlippingBitsDiv1 test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
