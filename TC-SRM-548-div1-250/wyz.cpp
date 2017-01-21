// BEGIN CUT HERE

// END CUT HERE
#line 5 "KingdomAndTrees.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn=55;

class KingdomAndTrees{
	int a[maxn],b[maxn],n;
	bool judge(int key){
		b[0]=max(1,a[0]-key);
		for (int i=1;i<n;++i)
			if (a[i]>b[i-1]) b[i]=max(b[i-1]+1,a[i]-key);
			else if (a[i]+key>b[i-1]) b[i]=b[i-1]+1;
			else return 0;
		return 1;
	}
	public:
	int minLevel(vector <int> heights){
		n=heights.size();
		for (int i=0;i<n;++i) a[i]=heights[i];
		int _l=-1,_r=1e9;
		while (_l+1<_r){
			int mid=(_l+_r)>>1;
			if (judge(mid)) _r=mid;
			else _l=mid;
		}
		return _r;
	}
};
