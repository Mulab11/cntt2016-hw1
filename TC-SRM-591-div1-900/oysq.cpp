#line 2 "StringPath.cpp"  
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

const int N = 8;
const int MOD = 1000000009;

int f[N][N][1 << N][1 << N];// f[i][j][sa][sb]表示x < i || x == i && y <= j的格子已经填充完毕，最后的m个格子与A，B的匹配状况分别是sa, sb的方案数

class StringPath {  
public:
	void upd(int &x, int v) {
		(x += v) %= MOD;
	}
	int countBoards(int n, int m, string A, string B) {
		if(A[0] != B[0] || A.back() != B.back()) return 0;
		memset(f, 0, sizeof f);
		f[0][0][1 << (m - 1)][1 << (m - 1)] = 1;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m - (i == n - 1); ++j) {
				int ni = j == m - 1 ? i + 1 : i, nj = j == m - 1 ? 0 : j + 1;
				for(int sa = 0; sa < (1 << m); ++sa)
					for(int sb = 0; sb < (1 << m); ++sb)
						if(f[i][j][sa][sb]) {
							int &v = f[i][j][sa][sb], x, y;
							// x, y分别表示(ni, nj)的前驱是否满足和A，B匹配
							if(j == m - 1) x = sa & 1, y = sb & 1;
							else x = (sa & 1) | (sa >> (m - 1) & 1), y = (sb & 1) | (sb >> (m - 1) & 1);
							if(A[ni + nj] == B[ni + nj]) {// 要么A[ni + nj]要么剩下的25个字母
								upd(f[ni][nj][sa >> 1 | x << (m - 1)][sb >> 1 | y << (m - 1)], v);
								upd(f[ni][nj][sa >> 1][sb >> 1], (int)(v * 25ll % MOD));
							}
							else {// 要么A[ni + nj]要么B[ni + nj]要么剩下的24个字母
								upd(f[ni][nj][sa >> 1 | x << (m - 1)][sb >> 1], v);
								upd(f[ni][nj][sa >> 1][sb >> 1 | y << (m - 1)], v);
								upd(f[ni][nj][sa >> 1][sb >> 1], (int)(v * 24ll % MOD));
							}
						}
			}
		// 统计答案，必须满足(n - 1, m - 1)对于A和B都是匹配的
		int ans = 0;
		for(int i = 1 << (m - 1); i < (1 << m); ++i)
			for(int j = 1 << (m - 1); j < (1 << m); ++j)
				upd(ans, f[n - 1][m - 1][i][j]);
		return ans;
	}    
};  
