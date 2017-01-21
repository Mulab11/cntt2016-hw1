// BEGIN CUT HERE

// END CUT HERE
#line 5 "HyperKnight.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;


class HyperKnight{
	int x[5],y[5];
	ll ans[8];
	public:
	long long countCells(int a, int b, int numRows, int numColumns, int k){
		int r=numRows,c=numColumns;
		if (a>b) swap(a,b);
		if (k==8) return 1LL*(r-b*2)*(c-b*2);
		if (k==6) return 1LL*(b-a)*(r+c-b*4)*2;
		if (k==4) return 1LL*(b-a)*(b-a)*4+1LL*a*(r+c-b*4)*2;
		if (k==3) return 1LL*a*(b-a)*8;
		if (k==2) return 1LL*a*a*4;
		return 0;
	}
};
