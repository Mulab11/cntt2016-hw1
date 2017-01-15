#line 2 "HyperKnight.cpp"  
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

int dx[] = {1, 1, -1, -1};
int dy[] = {1, -1, 1, -1};
// 4 directions

class HyperKnight {  
public:  
	long long countCells(int a, int b, int n, int m, int k) {
		int x[6] = {1, a + 1, b + 1, n - a + 1, n - b + 1, n + 1};// 4 constraints and 2 boundaries
		int y[6] = {1, a + 1, b + 1, m - a + 1, m - b + 1, m + 1};// same as above
		sort(x, x + 6), sort(y, y + 6);
		ll ans = 0;
		// enumerate every small rectangle
		for(int i = 0; i < 5; ++i)
			for(int j = 0; j < 5; ++j) {
				int tmp = 0;
				// (a, b) * (dx, dy)
				for(int r = 0; r < 4; ++r) {
					int p = x[i] + dx[r] * a, q = y[j] + dy[r] * b;
					if(p >= 1 && p <= n && q >= 1 && q <= m) tmp++;
				}
				// (b, a) * (dx, dy)
				for(int r = 0; r < 4; ++r) {
					int p = x[i] + dx[r] * b, q = y[j] + dy[r] * a;
					if(p >= 1 && p <= n && q >= 1 && q <= m) tmp++;
				}
				// 2 * 4 = total 8 directions
				if(tmp == k) ans += (ll)(x[i + 1] - x[i]) * (y[j + 1] - y[j]);// check if valid and update the answer
			}
		return ans;
	}    
};  
