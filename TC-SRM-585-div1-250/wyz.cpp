// BEGIN CUT HERE

// END CUT HERE
#line 5 "TrafficCongestion.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
#define P 1000000007
const int maxn=(1e6)+10;

class TrafficCongestion{
	int dp[maxn];
	public:
	int theMinCars(int treeHeight){
		dp[0]=1;dp[1]=2;
		for (int i=2;i<=treeHeight;++i)
			dp[i]=(1LL+dp[i-1]+(dp[i-2]<<1))%P;
		return (dp[treeHeight]-dp[treeHeight-1]+P)%P;
	}
};
