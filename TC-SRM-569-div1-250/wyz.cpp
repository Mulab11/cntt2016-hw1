// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheDevice.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;


class TheDevice{
	int n,m;
	public:
	int minimumAdditional(vector <string> plates){
		n=plates.size();
		m=plates[0].size();
		int ret=0;
		for (int i=0;i<m;++i){
			int cnt[2]={0,0};
			for (int j=0;j<n;++j)
				++cnt[plates[j][i]-48];
			ret=max(ret,max(0,1-cnt[0])+max(0,2-cnt[1]));
		}
		return ret;
	}
};
