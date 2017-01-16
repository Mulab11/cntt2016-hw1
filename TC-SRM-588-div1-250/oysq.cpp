#line 2 "GUMIAndSongsDiv1.cpp"  
#include <bits/stdc++.h> 

using namespace std;  

#define ui unsigned
#define ll long long

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}


class GUMIAndSongsDiv1 {  
public:  
	int maxSongs(vector <int> d, vector <int> t, int T) {  
		int n = SZ(d);
		// 对于唱歌的集合，为了尽量让rest的时间减少，肯定会按t从小到大或者从大到小来唱
		std::vector<pii> p;
		for(int i = 0; i < n; ++i) p.pb(mp(t[i], d[i]));
		std::sort(p.begin(), p.end());
		int ans = 0;
		for(int i = 0; i < n; ++i) {
			std::vector<int> q;
			for(int j = i; j < n; ++j) {// 枚举rest的时间
				int cur = p[j].fi - p[i].fi, cnt = 0;
				q.pb(p[j].se);
				std::sort(q.begin(), q.end());
				// 贪心选中的集合，确定rest的时间情况下，最小化d
				for(auto x : q)
					if(cur + x <= T) cur += x, cnt++;
				chkmax(ans, cnt);
			}
		}
		return ans;
	}    
};  
