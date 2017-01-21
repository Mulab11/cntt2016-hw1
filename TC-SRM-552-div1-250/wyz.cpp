// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxPaintingBalls.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;

class FoxPaintingBalls {
	public:
	long long theMax(long long R, long long G, long long B, int N){
		int n=N;
		if (n==1) return R+G+B;
		ll need=1LL*(n+1)*n/2;
		if (need%3==0) return min(R,min(G,B))/(need/3);
		ll ret=(R+G+B)/need;
		if (ret*(need/3)>min(R,min(G,B))) return min(R,min(G,B))/(need/3);
		else return ret;
	}
};
