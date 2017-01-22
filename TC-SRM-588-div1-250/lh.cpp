#include<cstdio>
//#include<string>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
struct nod{
	int tone,tim;
	bool operator < (const nod &a){
		return tone<a.tone;
	}
	bool operator > (const nod &a){
		return tone>a.tone;
	}
};

class GUMIAndSongsDiv1
{
	static const int maxn=55;
	int dp[maxn][maxn];
	nod rec[maxn];
	
	public:
	int maxSongs(vector <int> duration, vector <int> tone, int T){
		for (int i=0;i<maxn;++i)
			for (int j=0;j<maxn;++j){
				dp[i][j]=100000000;
				//printf("dp[%d][%d]=%d\n",i,j,dp[i][j]);
			}
		int n=tone.size();
		int ans=0;
		for (int i=0;i<n;++i){
			rec[i].tim=duration[i];
			rec[i].tone=tone[i];
			if (rec[i].tim<=T) ans=1;
		}
		if (ans==0) return 0;
		sort(rec,rec+n);
		for (int i=0;i<n;++i) 
		for (int i=0;i<n;++i){
			dp[i][1]=rec[i].tim;
			for (int j=2;j<=i+1;++j){
				for(int k=0;k<i;++k)
					dp[i][j]=min(dp[i][j],dp[k][j-1]+rec[i].tone-rec[k].tone);
				if (dp[i][j]<=T) dp[i][j]+=rec[i].tim;
				if(dp[i][j]<=T&&j>ans) ans=j;
				//if (dp[i][j]<=T) printf("dp[%d][%d]=%d\n",i,j,dp[i][j]);
			}
		}
		return ans;
	}
};