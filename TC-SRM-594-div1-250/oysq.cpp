#line 2 "AstronomicalRecords.cpp"  
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
const double eps = 1e-12;

int f[N + 9][N + 9];

class AstronomicalRecords {  
public:  
	int minimalPlanets(vector <int> a, vector <int> b) {
		int sa = SZ(a), sb = SZ(b), ret = sa + sb;
		for(int i = 0; i < sa; ++i)
			for(int j = 0; j < sb; ++j) {// 枚举两边相等的第一个位置
				std::vector<int> u, v;
				for(int k = i; k < sa; ++k) u.pb(a[k]);
				for(int k = j; k < sb; ++k) v.pb(b[k]);
				// 接下来做一个最长公共子序列的dp即可，这里的答案 = sa + sb - LCS
				for(int a = 0; a <= SZ(u); ++a)
					for(int b = 0; b <= SZ(v); ++b)
						f[a][b] = 0;
				for(int a = 0; a <= SZ(u); ++a)
					for(int b = 0; b <= SZ(v); ++b) {
						chkmax(f[a + 1][b], f[a][b]);
						chkmax(f[a][b + 1], f[a][b]);
						if(a < SZ(u) && b < SZ(v) && (ll)u[a] * v[0] == (ll)v[b] * u[0]) chkmax(f[a + 1][b + 1], f[a][b] + 1);
					}
				chkmin(ret, sa + sb - f[SZ(u)][SZ(v)]);// 更新答案
			}
		return ret;
	}    
};  
