// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheSquareRootDilemma.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;


class TheSquareRootDilemma{
	int n;
	vector<int> list;
	public:
	int countPairs(int N, int M){
		n=max(N,M);
		for (int i=1;i*i<=n;++i) list.push_back(i*i);
		int ret=0;
		for (int i=1;i<=N;++i){
			int b=1;
			for (int d:list)
				if (i%d==0) b=max(b,d);
			int a=i/b;
			for (int d:list)
				if (1LL*d*a<=M) ++ret;
		}
		return ret;
	}
};
