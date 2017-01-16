#line 2 "WolfDelaymasterHard.cpp"  
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

const int N = 2000000;
const int MOD = 1000000007;

char s[N + 9];
int sw[N + 9], so[N + 9];
int f[N + 9], fs[N + 9], add[N + 9];

int get(int l, int r, int *s) {// 根据前缀和数组s，求[l, r]区间和
	return s[r] - s[l - 1];
}

class WolfDelaymasterHard {  
public:  
	int countWords(int n, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd) {  
		std::fill(s + 1, s + n + 1, '?'), s[n + 1] = 0;
		ll x = w0;
		for(int i = 0; i < wlen; ++i) {
			s[x + 1] = 'w';
			x = (x * wmul + wadd) % n;
		}
		x = o0;
		for(int i = 0; i < olen; ++i) {
			s[x + 1] = 'o';
			x = (x * omul + oadd) % n;
		}
		for(int i = 1; i <= n; ++i) {// 记录o和w个数的前缀和
			sw[i] = sw[i - 1] + (s[i] == 'w');
			so[i] = so[i - 1] + (s[i] == 'o');
		}
		memset(f, 0, sizeof f), memset(add, 0, sizeof add);
		// f[i]表示1 ~ i字符串的方案数，fs[i] = sigma{f[j], j <= i}
		f[0] = fs[0] = 1;
		for(int i = 0, c = 0, lo = 0; i <= n; ++i) {
			(c += add[i]) %= MOD;
			// c = sigma{add[j], j <= i}
			if(s[i] != 'w' && !(i & 1)) {// 只有这样的点可以作为结尾点
				(f[i] += c) %= MOD;
				// 满足前半部分至少一个w的长度是一个区间，用两个二分搞出上下界
				int l1 = 0, l2 = 0;
				int l = 1, r = i / 2;
				while(l <= r) {
					int mid = (l + r) >> 1;
					int w1 = get(i - 2 * mid + 1, i - mid, sw), w2 = get(i - mid + 1, i, sw);
					int o1 = get(i - 2 * mid + 1, i - mid, so);
					if(w1 && !o1 && !w2) r = mid - 1, l1 = mid;
					else if(w2) r = mid - 1;
					else if(!w1) l = mid + 1;
					else {
						if(lo >= i - 2 * mid + 1) r = mid - 1;
						else l = mid + 1;
					}
				}
				l = 1, r = i / 2;
				while(l <= r) {
					int mid = (l + r) >> 1;
					int w1 = get(i - 2 * mid + 1, i - mid, sw), w2 = get(i - mid + 1, i, sw);
					int o1 = get(i - 2 * mid + 1, i - mid, so);
					if(w1 && !o1 && !w2) l = mid + 1, l2 = mid;
					else if(w2) r = mid - 1;
					else if(!w1) l = mid + 1;
					else {
						if(lo >= i - 2 * mid + 1) r = mid - 1;
						else l = mid + 1;
					}
				}
				// l1 <= 长度 / 2 <= l2
				if(l1 && l2) (f[i] += (fs[i - 2 * l1] - (i == 2 * l2 ? 0 : fs[i - 2 * l2 - 2]) + MOD) % MOD) %= MOD;// 整个区间转移
				// 如果前半部分没有w，那么全都是?，对于某个i，能贡献到的j(j > i)，也是一个区间，二分出这个区间，用add完成区间加法，左端点加右端点减
				if(s[i + 1] == '?') {
					int l3 = 0;
					l = i + 1, r = i + (n - i) / 2;
					while(l <= r) {
						int mid = (l + r + 1) >> 1;
						if(!get(i + 1, mid, sw) && !get(i + 1, mid, so) && !get(mid + 1, 2 * mid - i, sw)) l = mid + 1, l3 = mid;
						else r = mid - 1;
					}
					if(l3) (add[i + 2] += f[i]) %= MOD, (add[i + (l3 - i) * 2 + 2] += MOD - f[i]) %= MOD;
				}
			}
			else if(s[i] == 'w') {
				while(get(lo + 1, i, so)) ++lo;// 维护离i最近的w的最近的o的位置
			}
			fs[i] = (fs[i - 1] + f[i]) % MOD;
		}
		return f[n];
	}  
};  
