#include<cstdio>
#include<set>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class CuttingBitString{
	static const int maxn=55;
	int dp[maxn];
	set<long long> rec;
	
	bool check(string &a,int l,int r){
		if (a[l]=='0') return false;
		long long ret=0;
		for (int i=l;i<r;++i){
			ret=ret*2+a[i]-'0';
		}
		return rec.find(ret)!=rec.end();
	}
	
	public:
	int getmin(string S){
		long long t=1;
		while(t<(1LL<<50)){
			rec.insert(t);
			t*=5;
		}
		memset(dp,-1,sizeof(dp));
		dp[0]=0;
		int n=S.length();
		for (int i=1;i<=n;++i){
			for (int j=0;j<i;++j) if (dp[j]!=-1)
			if (check(S,j,i)){
				if (dp[i]==-1)dp[i]=dp[j]+1;
				else dp[i]=min(dp[i],dp[j]+1);
			}
		}
		return dp[n];
	}
};
