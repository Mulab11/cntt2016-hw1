// BEGIN CUT HERE

// END CUT HERE
#line 5 "PiecewiseLinearFunction.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=55;

class PiecewiseLinearFunction{
	int n;
	pair<int,int> a[maxn];
	priority_queue<int,vector<int> ,greater<int> > q;
	public:
	int maximumSolutions(vector <int> Y){
		n=Y.size();
		for (int i=1;i<n;++i){
			if (Y[i]==Y[i-1]) return -1;
			a[i]=make_pair(Y[i-1]*2,Y[i]*2-(i<n-1));
			if (a[i].first>a[i].second) swap(a[i].first,a[i].second+=2*(i<n-1));
		}
		int ret=0;
		sort(a+1,a+n);
		while (q.size()) q.pop();
		for (int i=1;i<n;++i){
			q.push(a[i].second);
			while (q.top()<a[i].first) q.pop();
			ret=max(ret,(int)q.size());
		}
		return ret;
	}
};
