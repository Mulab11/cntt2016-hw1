#line 2 "FlippingBitsDiv1.cpp"  
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

const int N = 300;
const int INF = 1e9;

std::string s;
int n, m, d;

class FlippingBitsDiv1 {  
public:  
	int getmin(vector <string> S, int M) {
		s.clear();
		for(auto i : S) s += i;
		n = SZ(s), m = M, d = (n + m - 1) / m;
		// 根据题意，每个长度为m的可以看成一段，它们都要相等
		int ans = INF;
		if(m <= 17) {
			// 当m <= sqrt(n)时，可以枚举最终的长度为m的串
			// dp出变成这样的最小代价即可
			static int p[N + 9][2], f[N + 9];
			for(int g = 0; g < (1 << m); ++g) {// 枚举长度为m的单位串
				// p[i][0 / 1] 表示第i段是否翻转整串的代价
				for(int i = 0; i < n; i += m) {// 计算代价
					int &p0 = p[i / m][0], &p1 = p[i / m][1];
					p0 = p1 = 0;
					for(int j = 0; j < m && i + j < n; ++j) {
						p0 += s[i + j] != ((g >> j) & 1) + '0';
						p1 += s[i + j] == ((g >> j) & 1) + '0';
					}
				}
				for(int i = 0, pre = 0, val = 0; i < d; ++i) {// dp
					f[i] = (i ? f[i - 1] : 0) + p[i][0];
					pre += p[i][1];
					chkmin(f[i], val + pre + 1);
					chkmin(val, f[i] - pre + 1);// 前缀最小值优化
				}
				chkmin(ans, f[d - 1]);// 更新答案
			}
		}
		else {
			// 否则ceil(n / m) <= sqrt(n)，这样我们可以枚举每一段是否整串翻转，再对每一位贪心
			for(int g = 0; g < (1 << d); ++g) {
				int cur = 0;
				// 计算整串翻转的代价
				for(int i = 0; i < d; ++i)
					if(g >> i & 1) {
						int j = i;
						while(j < d - 1 && (g >> (j + 1) & 1)) ++j;
						cur += 1 + (i > 0);
						i = j;
					}
				// 对每一位贪心
				for(int i = 0; i < m; ++i) {
					int c[2] = {0};
					for(int j = 0; j < 2; ++j)// 枚举当前位为j
						for(int k = i; k < n; k += m)
							c[j] += (g >> (k / m) & 1) ^ (s[k] - '0') ^ j;
					cur += std::min(c[0], c[1]);// 取最小的
				}
				chkmin(ans, cur);// 更新答案
			}
		}
		return ans;
	}    
};  
