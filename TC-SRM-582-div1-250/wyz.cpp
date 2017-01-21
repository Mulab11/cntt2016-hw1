// BEGIN CUT HERE

// END CUT HERE
#line 5 "SpaceWarDiv1.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=55;

class SpaceWarDiv1{
	int n;
	pair<int,ll> a[maxn];
	public:
	long long minimalFatigue(vector <int> magicalGirlStrength, vector <int> enemyStrength, vector<long long> enemyCount){
		n=enemyStrength.size();
		for (int i=0;i<n;++i) a[i]=make_pair(enemyStrength[i],enemyCount[i]);
		sort(a,a+n);
		sort(magicalGirlStrength.begin(),magicalGirlStrength.end());
		int m=magicalGirlStrength.size(),p=m;
		ll ret=0,s=0;
		for (int i=n-1;i>=0;--i){
			s+=a[i].second;
			while (p&&magicalGirlStrength[p-1]>=a[i].first) --p;
			if (p==m) return -1;
			ret=max(ret,(s-1)/(m-p)+1);
		}
		return ret;
	}
};
