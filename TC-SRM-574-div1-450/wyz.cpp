// BEGIN CUT HERE

// END CUT HERE
#line 5 "PolygonTraversal.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn=20;

class PolygonTraversal{
	int bin[maxn];
	int n;
	ll dp[300005][maxn];
	void work(){
		bool valid[maxn];
		for (int msk=0;msk<bin[n];++msk)for (int i=0;i<n;++i)if (dp[msk][i]){
			memset(valid,1,sizeof(valid));
			for (int j=(i+1)%n;(msk&bin[j])==0;j=(j+1)%n) valid[j]=0;
			for (int j=(i+n-1)%n;(msk&bin[j])==0;j=(j+n-1)%n) valid[j]=0;
			for (int j=0;j<n;++j)if ((msk&bin[j])==0&&valid[j])
				dp[msk|bin[j]][j]+=dp[msk][i];
		}
	}
	public:
	long long count(int N, vector <int> points){
		n=N;
		for (int i=0;i<=n;++i) bin[i]=1<<i;
		
		int tmp=0;
		for (int i=0;i<points.size();++i)
			tmp|=bin[points[i]%n];
		
		memset(dp,0,sizeof(dp));
		dp[tmp][points.back()%n]=1;
		work();
		
		ll ret=0;
		for (int i=0;i<n;++i)
			if ((points[0]-1)%n!=i&&(points[0]+1)%n!=i)
				ret+=dp[bin[n]-1][i];
		return ret;
	}
};
