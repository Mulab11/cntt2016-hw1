#line 2 "LittleElephantAndBoard.cpp"
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#define clear(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define son e[i].t
#define oo 0x3f3f3f3f
#define maxn 1000010
#define mo 1000000007
typedef long long ll;
using namespace std;
int frac[maxn], ifrac[maxn], bit[maxn];
void add(int &a, int b){ a += b; while (a >= mo) a -= mo;}
int C(int n, int m)
{
	if (n < m) return 0;
	return 1ll * frac[n] * ifrac[m] % mo * ifrac[n - m] % mo;
}
int calc(int a, int b, int c)
{
	int ret = 0;
	if (a <= 0 || b < 0 || c < 0) return 0;
	for (int m = a - 1; m <= a; ++ m){
		if (m < 0) continue;
		for (int p = 0; p <= m; ++ p){
			int tmp = b - c + m - p;
			if (tmp < 0 || tmp > 2 * m || (tmp & 1)) continue;
			if (tmp / 2 - b + c < 0 || tmp / 2 - b + c > m) continue;
			int cnt = (b + c + m - p) / 2;
			add(ret, 1ll * C(cnt - m + m - 1, m - 1) * bit[p] % mo * C(m, p) % mo * C(m - p, tmp / 2) % mo);
		}
	}
	return ret;
}
class LittleElephantAndBoard
{
	public:
		int getNumber(int M, int R, int G, int B)
		{
			frac[0] = ifrac[0] = ifrac[1] = bit[0] = 1;
			for (int i = 2; i <= M; ++ i) ifrac[i] = (mo - 1ll * (mo / i) * ifrac[mo % i] % mo) % mo;
			for (int i = 1; i <= M; ++ i) frac[i] = 1ll * frac[i - 1] * i % mo;
			for (int i = 1; i <= M; ++ i) ifrac[i] = 1ll * ifrac[i - 1] * ifrac[i] % mo;
			for (int i = 1; i <= M; ++ i) bit[i] = 2ll * bit[i - 1] % mo;
			int ans = 0;
			R = M - R; G = M - G; B = M - B;
			add(ans, calc(R, G, B)); add(ans, calc(G, B, R)); add(ans, calc(B, R, G));
			return 2ll * ans % mo;
		}
};
