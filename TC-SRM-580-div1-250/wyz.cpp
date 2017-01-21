// BEGIN CUT HERE

// END CUT HERE
#line 5 "EelAndRabbit.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=55;

class EelAndRabbit{
	int n;
	public:
	int getmax(vector <int> l, vector <int> t){
		n=l.size();
		int ret=0;
		for (int i=0;i<n;++i)for (int j=0;j<n;++j){
			int now=0;
			for (int k=0;k<n;++k)if (t[k]<=t[i]&&t[i]<=t[k]+l[k]||t[k]<=t[j]&&t[j]<=t[k]+l[k])++now;
			ret=max(ret,now);
		}
		return ret;
	}
};
