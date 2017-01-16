#line 5 "EllysBulls.cpp"
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

const int N = 50;

int n, m;
std::vector<std::string> g;
std::vector<int> b;
std::map<std::vector<int>, int> f;
std::map<std::vector<int>, std::string> s;
int pw[6];

struct EllysBulls {
    string getNumber(vector <string> _g, vector <int> _b) {
		g = _g;
		b = _b;
		n = SZ(g);
		m = SZ(g[0]);
		pw[0] = 1;
		for(int i = 1; i <= 5; ++i) {// 预处理10的幂
			pw[i] = pw[i - 1] * 10;
		}
		f.clear();
		s.clear();
		// 枚举前m / 2位的值，将相等的位数信息存在map中
		// f 存个数, s 存对应的字符串
		for(int i = 0; i < pw[m / 2]; ++i) {
			std::string x;
			for(int j = m / 2 - 1; j >= 0; --j) {
				x += i / pw[j] % 10 + '0';// 将i变成字符串
			}
			std::vector<int> com;
			for(int j = 0; j < n; ++j) {// 枚举每个限制条件，计算相等个数
				int c = 0;
				for(int k = 0; k < m / 2; ++k) {
					c += g[j][k] == x[k];
				}
				com.pb(c);
			}
			// 将信息放在map中
			if(!f.count(com)) {
				f[com] = 1;
			}
			else {
				f[com]++;
			}
			s[com] = x;
		}
		bool flag = false;
		std::string ret;
		for(int i = 0; i < pw[m - m / 2]; ++i) {
			// 枚举后m - m / 2位的值，查询map中有没有互补的信息
			std::string x;
			for(int j = m - m / 2 - 1; j >= 0; --j) {
				x += i / pw[j] % 10 + '0';
			}
			std::vector<int> com;
			for(int j = 0; j < n; ++j) {
				int c = 0;
				for(int k = 0; k < m - m / 2; ++k) {
					c += g[j][k + m / 2] == x[k];
				}
				com.pb(b[j] - c);
			}
			if(f.count(com)) {
				if(f[com] > 1) {// 对应的个数 > 1
					return "Ambiguity";
				}
				else if(f[com] == 1) {// = 1
					if(flag) {// 如果之前就有了，显然已经 > 1了
						return "Ambiguity";
					}
					else {// 之前没有，保存答案
						flag = true;
						ret = s[com] + x;
					}
				}
			}
		}
		if(!SZ(ret)) {// 没有合法的
			return "Liar";
		}
		else {
			return ret;
		}
    }
};  