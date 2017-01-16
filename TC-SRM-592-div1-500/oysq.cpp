#line 2 "LittleElephantAndPermutationDiv1.cpp"  
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
const int MOD = 1000000007;

int f[N + 9][N + 9][N * N + 9];
// f[i][j][k]表示放了前1 ~ i个数，有j个数放在前i个位置，前i个位置的和为k

void upd(int &x, int v) {
	(x += v) %= MOD;
}

class LittleElephantAndPermutationDiv1 {  
public:  
	int getNumber(int n, int K) {
		// 先假定A就是1,2,...,n的排列
		memset(f, 0, sizeof f);
		f[0][0][0] = 1;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j <= i; ++j)
				for(int k = 0; k <= i * i; ++k)
					if(f[i][j][k]) {
						int v = f[i][j][k];
						upd(f[i + 1][j + 1][k + i + 1], v);// i + 1就放在i + 1的位置
						for(int a = 0; a < 2; ++a)// a = 1表示i + 1放在1 ~ i的位置
							for(int b = 0; b < 2; ++b)// b = 1表示i + 1位置放了 <= i的数
								upd(f[i + 1][j + a + b][k + (a + b) * (i + 1)], (ll)v * (a ? i - j : 1) * (b ? i - j : 1) % MOD);
					}
		int ans = 0;
		for(int i = K; i <= n * n; ++i)// 统计答案
			upd(ans, f[n][n][i]);
		for(int i = 1; i <= n; ++i) ans = (ll)ans * i % MOD;// 之前假定A是1,2,...,n的排列，显然对于每个排列的答案都是一样的
		return ans;
	}    
};  
