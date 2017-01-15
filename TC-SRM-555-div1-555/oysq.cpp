#line 2 "XorBoard.cpp"  
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

const int N = 3100;
const int MOD = 555555555;

int c[N + 9][N + 9];

int fpm(int a, int b) {
	int ret = 1;
	while(b) {
		if(b & 1) ret = (ll)ret * a % MOD;
		a = (ll)a * a % MOD, b >>= 1;
	}
	return ret;
}

class XorBoard {  
public:  
	int count(int H, int W, int Rcount, int Ccount, int S) {
		// get combinatorics
		for(int i = 0; i <= N; ++i) {
			c[i][0] = 1;
			for(int j = 1; j <= i; ++j)
				c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
		}
		int ret = 0;
		for(int i = 0; i <= H && i <= Rcount; ++i)// number of rows really changed("really changed" means odd number of operations on it)
			for(int j = 0; j <= W && j <= Ccount; ++j)// number of colums really changed
				if(i * W + j * H - i * j * 2 == S) {// check number of '1'
					if((Rcount - i) % 2 == 0 && (Ccount - j) % 2 == 0) {
						(ret += (ll)c[H][i] * c[(Rcount - i) / 2 + H - 1][H - 1] % MOD * c[W][j] % MOD * c[(Ccount - j) / 2 + W - 1][W - 1] % MOD) %= MOD;
					}
				}
		return ret;
	}    
};  
