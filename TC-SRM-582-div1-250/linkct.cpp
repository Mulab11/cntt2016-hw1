#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int MAXM = 55;

class SpaceWarDiv1{
public:
	struct Enemy{
		int p; LL c;
		bool operator < (const Enemy &rhs) const{
			return p < rhs.p;
		}
	}e[MAXM];
	int n, m; vector <int> power;
	bool check(LL limit){
		int i, j; LL remain;
		for(i = j = 0, remain = limit; i < m; ++ i){
			while(j < n && power[j] < e[i].p) ++ j, remain = limit;
			while(j < n && remain < e[i].c) ++ j, remain += limit;
			if(j == n) return false;
			remain -= e[i].c; if(!remain) ++ j, remain = limit;
		} return true;
	}
	LL minimalFatigue(vector <int> power_, vector <int> epower, vector <LL> ecnt){
		int i; LL l = 0, r = 0, mid; power = power_;
		n = power.size(), m = epower.size();
		for(i = 0; i < m; ++ i){
			e[i].p = epower[i], e[i].c = ecnt[i];
			r += e[i].c;
		}
		sort(e, e + m), sort(power.begin(), power.end());
		if(e[m - 1].p > power[n - 1]) return -1;
		while(l < r){
			mid = (l + r) >> 1LL;
			if(check(mid)) r = mid;
			else l = mid + 1;
		} return r;
	}
};
