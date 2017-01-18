#line 2 "ICPCBalloons.cpp"
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
#define cl(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define oo 0x3f3f3f3f
#define maxn 90
#define maxs 33000
typedef long long ll;
using namespace std;
int n;
vector <int> a, M, L;
int f[maxn][maxs], g[maxn][maxs]; // f[i][s]表示考虑size为M的前i种颜色，满足了s集合中题目的需求，所需的最少填色次数。g对应size为L的颜色
int Msum, Lsum, sum; // Msum为size为M的气球的个数和，sum是所有题目的需求和
void upd(int &a, int b) {
	if (b < a) a = b;
}
void calc(int f[maxn][maxs], vector<int> b) { // b是可供使用的气球集合，b[i]表示第i种颜色的气球个数
	int m = b.size();
	f[0][0] = 0;
	for (int i = 0; i < m; ++i)
		for (int s = 0; s < (1 << n); ++s) {
			for (int j = 0; j < n; ++j)
				if (!(s & (1 << j))) // 把当前这种颜色的气球用于第j道题
					upd(f[i + 1][s | (1 << j)], f[i][s] + max(0, a[j] - b[i])); // 若b[i]不足以提供a[j],则需要a[j] - b[i]个其他颜色的气球被涂色
			upd(f[i + 1][s], f[i][s]);
		}
}
class ICPCBalloons {
	public:
		int minRepaintings(vector <int> cnt, string balloonSize, vector <int> maxAccepted) {
			a = maxAccepted; n = a.size();
			M.clear(); L.clear(); 
			sum = Lsum = Msum = 0;
			for (int i = 0; i < cnt.size(); ++i) // 把气球根据size分成两类
				if (balloonSize[i] == 'M')
					M.pb(cnt[i]), Msum += cnt[i]; 
				else
					L.pb(cnt[i]), Lsum += cnt[i];
			for (int i = 0; i < n; ++i)
				M.pb(0), L.pb(0); // 可以改成当前没有的颜色
			memset(f, 0x3f, sizeof(f)); memset(g, 0x3f, sizeof(g));
			calc(f, M); calc(g, L);
			for (int i = 0; i < n; ++i) sum += a[i];
			int ans = oo;
			for (int s = 0; s < (1 << n); ++s) { // 枚举用Msize的题目集合
				int t = (1 << n) - 1 - s;
				int ssum = 0; // s中题目的需求和
				for (int i = 0; i < n; ++i)
					if (s & (1 << i)) 
						ssum += a[i];
				if (ssum > Msum || sum - ssum > Lsum) continue; // 若气球个数不足
				ans = min(ans, f[M.size()][s] + g[L.size()][t]); 
			}
			return (ans == oo) ? -1 : ans;
		}
};
