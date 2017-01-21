// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheBrickTowerMediumDivOne.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn=55;

int h[maxn];
bool cmp(const int x,const int y){
	if (h[x]!=h[y]) return h[x]<h[y];
	return x<y;
}

class TheBrickTowerMediumDivOne {
	int n;
	public:
	vector <int> find(vector <int> heights){
		vector<int> ret,a;
		n=heights.size();
		for (int i=0;i<n;++i) h[i]=heights[i];
		for (int i=0;i<n;++i)
			if (i==0||h[ret.back()]>=h[i]) ret.push_back(i);
			else a.push_back(i);
		sort(a.begin(),a.end(),cmp);
		for (int i:a) ret.push_back(i);
		return ret;
	}
};
