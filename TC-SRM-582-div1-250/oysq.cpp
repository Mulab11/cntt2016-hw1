#line 2 "SpaceWarDiv1.cpp"  
#include <bits/stdc++.h> 

using namespace std;  

#define ui unsigned
#define ll long long

#define pil std::pair<int, ll>
#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}


class SpaceWarDiv1 {
private:
	bool check(std::vector<int> p, std::vector<pil> q, ll f) {// 贪心每次攻击能攻击的strength最大的敌人
		for(int i = SZ(p) - 1, j = SZ(q) - 1; i >= 0; --i) {
			ll res = f;
			while(j >= 0 && q[j].fi > p[i]) --j;
			while(j >= 0) {
				if(q[j].se > res) {
					q[j].se -= res;
					break;
				}
				else {
					res -= q[j].se, q[j].se = 0;
					j--;
				}
			}
		}
		for(int i = 0; i < SZ(q); ++i)
			if(q[i].se) return false;
		return true;
	}
public:  
	long long minimalFatigue(vector <int> p, vector <int> b, vector<long long> c) {
		std::vector<pil> q;
		for(int i = 0; i < SZ(b); ++i) q.pb(mp(b[i], c[i]));
		std::sort(p.begin(), p.end());
		std::sort(q.begin(), q.end());
		ll l = 0, r = 1e16;
		while(l < r) {// 二分答案
			ll mid = (l + r) >> 1;
			if(check(p, q, mid)) r = mid;
			else l = mid + 1;
		}
		return l == (ll)1e16 ? -1 : l;
	}  
};  
