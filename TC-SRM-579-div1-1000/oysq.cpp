#line 2 "RockPaperScissors.cpp"  
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

int n;
double f[N + 9][N + 9][N + 9];// f[a][b][c] 表示随出来的a + b + c个色子出现了a个rock，b个paper，c个scissor的概率

class RockPaperScissors {  
public:  
	double bestScore(vector <int> r, vector <int> p, vector <int> s) {  
		memset(f, 0, sizeof f);
		f[0][0][0] = 1, n = SZ(r);
		for(int i = 0; i < n; ++i)
			for(int a = i + 1; a >= 0; --a)
				for(int b = i + 1 - a; b >= 0; --b)
					for(int c = i + 1 - a - b; c >= 0; --c) {
						double ch = (double)(a + b + c) / (i + 1);// 第i个出现的概率
						f[a][b][c] *= (1 - ch);// 不出现
						// 出现
						if(a) f[a][b][c] += ch * r[i] / 300 * f[a - 1][b][c];
						if(b) f[a][b][c] += ch * p[i] / 300 * f[a][b - 1][c];
						if(c) f[a][b][c] += ch * s[i] / 300 * f[a][b][c - 1];
					}
		// 逆推期望
		double ret = 0;
		for(int a = 0; a < n; ++a)
			for(int b = 0; a + b < n; ++b)
				for(int c = 0; a + b + c < n; ++c) {
					// 下一步r,p,s的概率
					double u = f[a + 1][b][c] * (a + 1) / (a + 1 + b + c);// rock
					double v = f[a][b + 1][c] * (b + 1) / (a + b + 1 + c);// paper
					double w = f[a][b][c + 1] * (c + 1) / (a + b + c + 1);// scissor
					double e1 = 3 * w + 1 * u, e2 = 3 * u + 1 * v, e3 = 3 * v + 1 * w;// 当前三种决策的期望贡献
					ret += std::max(std::max(e1, e2), e3);// 取最大的
				}
		return ret;
	}    
};  
