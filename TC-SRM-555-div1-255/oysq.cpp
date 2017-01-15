#line 2 "CuttingBitString.cpp"  
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

const int N = 100;

int bit[N + 9][N + 9];
std::string str[N + 9];
int len[N + 9];

int f[N + 9];

class CuttingBitString {  
public:  
	int getmin(string s) {
		memset(len, 0, sizeof len);
		memset(bit, 0, sizeof bit);
		// get 5 ^ x in binary representation
		int n = SZ(s);
		bit[0][0] = 1, len[0] = 1, str[0] = '1';
		for(int i = 1; i <= n; ++i) {
			// x * 5 = (x << 2) + x
			len[i] = len[i - 1] + 2;
			for(int j = 0; j < len[i - 1]; ++j)
				bit[i][j + 2] = bit[i - 1][j];
			for(int j = 0; j < len[i]; ++j) {
				bit[i][j] += bit[i - 1][j];
				bit[i][j + 1] += bit[i][j] >= 2;
				bit[i][j] -= 2 * (bit[i][j] >= 2);
			}
			if(bit[i][len[i]]) len[i]++;
			str[i].clear();
			for(int j = len[i] - 1; j >= 0; --j)
				str[i] += (char)(bit[i][j] + '0');
			// std::cout << i << ' ' << str[i] << std::endl;
		}
		// dp, f[i] = min(f[j] + 1, valid(j + 1, i))
		std::fill(f + 1, f + n + 1, N), f[0] = 0;
		for(int i = 1; i <= n; ++i)
			for(int j = 0; len[j] <= i; ++j)
				if(s.substr(i - len[j], len[j]) == str[j])
					chkmin(f[i], f[i - len[j]] + 1);
		if(f[n] > n) return -1;// no solution
		else return f[n];
	}    
};  
