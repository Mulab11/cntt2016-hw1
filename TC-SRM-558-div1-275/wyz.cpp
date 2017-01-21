// BEGIN CUT HERE

// END CUT HERE
#line 5 "Stamp.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
inline void Min(int &x,int y){if (x<0||y<x)x=y;}

const int maxn=55;

class Stamp{
	int n;
	int dp[maxn];
	int cnt[2333];
	public:
	int getMinimumCost(string desiredColor, int stampCost, int pushCost){
		n=desiredColor.size();
/*		memset(valid,0,sizeof(valid));
		for (int i=0;i<n;++i){
			memset(cnt,0,sizeof(cnt));
			for (int j=i;j<n;++j){
				++cnt[(int)desiredColor[j]];
				if ((cnt['R']>0)+(cnt['G']>0)+(cnt['B']>0)>1) break;
				valid[i][j]=1;
			}
		}*/
		int ret=-1;
		for (int len=1;len<=n;++len){
			for (int i=0;i<n;++i){
				dp[i]=-1;
				memset(cnt,0,sizeof(cnt));
				for (int j=i;j>=0;--j){
					++cnt[(int)desiredColor[j]];
					if ((cnt['R']>0)+(cnt['G']>0)+(cnt['B']>0)>1) break;
					int tmp=(j?dp[j-1]:0);
					if (i-j+1<len||tmp<0) continue;
					Min(dp[i],tmp+(i-j)/len+1);
				}
			}
			if (dp[n-1]>=0) Min(ret,stampCost*len+pushCost*dp[n-1]);
		}
		return ret;
	}
};
