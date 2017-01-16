// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheJediTest.cpp"
#include <bits/stdc++.h>

using namespace std;

#define SZ(x) (int)(x).size()
#define pb push_back
#define mp make_pair
#define fi first
#define se second

typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;
typedef long long ll;
typedef pair<int,int> pii;

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

struct TheJediTest {
    int minimumSupervisors(vector <int> v, int K) {
		int n = SZ(v), ans = 0;
		for(int i = 0; i < n; ++i) {
			// 经典贪心，每层能放就放，多得推给下两层减掉
			ans += (v[i] + K - 1) / K;// 注意向上取整不能(x - 1) / K + 1，当x = 0的时候会挂
			int ex = (K - v[i] % K) % K, ex2;
			if(i < n - 1) {
				ex2 = std::min(ex, v[i + 1]);
				v[i + 1] -= ex2, ex -= ex2;
			}
			if(i < n - 2) v[i + 2] -= std::min(ex, v[i + 2]);
		}
		return ans;
    }    
};
