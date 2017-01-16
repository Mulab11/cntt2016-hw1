#line 2 "TravelOnMars.cpp"  
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

const int N = 50;

class TravelOnMars {  
public:  
	int minTimes(vector <int> r, int st, int ed) {
		int n = SZ(r), ans[N + 9] = {0};
		memset(ans, -1, sizeof ans);
		std::queue<int> q;
		q.push(st), ans[st] = 0;
		while(!q.empty()) {// bfs
			int x = q.front();
			q.pop();
			for(int i = 0; i < n; ++i) {
				int d = std::min(abs(x - i), n - abs(x - i));
				if(d <= r[x] && ans[i] == -1) {
					ans[i] = ans[x] + 1;
					q.push(i);
				}
			}
		}
		return ans[ed];
	}
};  
