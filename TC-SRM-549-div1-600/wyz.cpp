// BEGIN CUT HERE

// END CUT HERE
#line 5 "MagicalHats.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn=15;
const int inf=233;

class MagicalHats{
	int bin[maxn];
	
	int x[maxn],y[maxn],n;
	
	int r,c,cntr[maxn],cntc[maxn];
	int coin,guess;
	
	int dp[1666666];
	void dfs(int u,int cnt,int mask){
		if (cnt>coin||n-u+cnt<coin) return;
		if (u==n){
			for (int i=0;i<r;++i)if (cntr[i]&1) return;
			for (int i=0;i<c;++i)if (cntc[i]&1) return;
//			printf("[qwq]%d\n",mask);
			dp[mask]=0;
			return;
		}
		++cntr[x[u]];++cntc[y[u]];
		dfs(u+1,cnt+1,mask*3+1);
		--cntr[x[u]];--cntc[y[u]];
		dfs(u+1,cnt,mask*3);
	}
	
	int now[maxn];
	public:
	int findMaximumReward(vector <string> board, vector <int> coins, int numGuesses){
		for (int i=bin[0]=1;i<=13;++i) bin[i]=bin[i-1]*3;
		guess=numGuesses;
		coin=coins.size();
		n=0;
		r=board.size();c=board[0].size();
		for (int i=0;i<r;++i)for (int j=0;j<c;++j)
			if (board[i][j]=='H'){x[n]=i;y[n]=j;n++;cntr[i]++;cntc[j]++;}
		memset(dp,1,sizeof(dp));
		dfs(0,0,0);
		
//		for (int i=0;i<bin[n];++i) printf("%d %d\n",i,dp[i]);
		for (int i=0;i<bin[n];++i){
			int tmp=i,cnt[3]={0,0,0};
			for (int j=0;j<n;++j,tmp/=3)
				++cnt[now[j]=tmp%3];
//			printf("%d %d\n",i,dp[i]);
//			if (dp[i]==0){for (int j=0;j<n;++j)printf("%d",now[j]);puts("");}
			if (cnt[2]+guess<n){
				for (int j=0;j<n;++j)
					if (now[j]<2&&dp[i]==0) dp[i-bin[j]*now[j]+bin[j]*2]=0;
				continue;
			}
			if (cnt[2]+guess==n){
				if (dp[i]==0) dp[i]=cnt[1];
				continue;
			}
			dp[i]=0;
			for (int j=0;j<n;++j)
				if (now[j]==2) dp[i]=max(dp[i],min(dp[i-bin[j]*2+bin[j]*1],dp[i-bin[j]*2]));
		}
		
//		for (int i=0;i<bin[n];++i) printf("%d\n",dp[i]);
		
		sort(coins.begin(),coins.end());
		if (dp[bin[n]-1]>n) return -1;
		int ret=0;
		for (int i=0;i<dp[bin[n]-1];++i)
			ret+=coins[i];
		return ret;
	}
};
