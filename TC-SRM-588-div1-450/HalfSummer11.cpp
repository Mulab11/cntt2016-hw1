#line 2 "KeyDungeonDiv1.cpp"
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
#define maxn 150
#define maxs 4100
typedef long long ll;
using namespace std;
/*
   考虑dp, f[S][R][G][W]表示到过的房间集合为S，三种钥匙个数为R, G, W，这种状态是否可达。
   发现使用钥匙时，一定是优先使用R和G，保留万用的W，于是改用f[S][R][G]表示这种情况下，W钥匙最多有多少。
   进一步地，发现S确定时，只要给定R和W，就可以推出G，于是状态精简为f[S][R]
*/
int n, f[maxs][maxn], sR[maxs], sG[maxs], sW[maxs], tR[maxs], tG[maxs];
// n是房间个数，f[s][R]表示已经进去的房间集合为s，目前R钥匙的个数为R时，W钥匙最多有多少。
// sR[s], sG[s], sW[s], tR[s], tG[s]分别记录集合s中rR, rG, rW, dR, dG的和
void gmax(int &a, int b) {
	if (b > a) a = b;
}
class KeyDungeonDiv1 {
	public:
		int maxKeys(vector <int> dR, vector <int> dG, vector <int> rR, vector <int> rG, vector <int> rW, vector <int> keys) {
			n = dR.size();
			cl(f); cl(sR); cl(sG); cl(sW); cl(tR); cl(tG);
			for (int i = 0; i < n; ++i) {
				sR[1 << i] = rR[i];
				sG[1 << i] = rG[i];
				sW[1 << i] = rW[i];
				tR[1 << i] = dR[i];
				tG[1 << i] = dG[i];
			}
			for (int s = 0; s < (1 << n); ++s) { // 预处理sR[], sG[], sW[], tR[], tG[]
				int u = (s & (-s));
				sR[s] = sR[s - u] + sR[u];
				sG[s] = sG[s - u] + sG[u];
				sW[s] = sW[s - u] + sW[u];
				tR[s] = tR[s - u] + tR[u];
				tG[s] = tG[s - u] + tG[u];
			}
			memset(f, -0x3f, sizeof(f));
			f[0][keys[0]] = keys[2]; // 初始状态
			int ans = 0;
			for (int s = 0; s < (1 << n); ++s)
				for (int i = 0; i <= (n + 1) * 10; ++i)
					if (f[s][i] >= 0) {
						int R = i, W = f[s][i], G = keys[1] + sG[s] - (tG[s] - (keys[2] + sW[s] - W - (tR[s] - (keys[0] + sR[s] - R)))); // 推出G
						ans = max(ans, R + G + W);
						for (int j = 0; j < n; ++j)
							if (!(s & (1 << j)) && W >= max(0, dR[j] - R) + max(0, dG[j] - G))  // 可以进入房间j
								gmax(f[s | (1 << j)][max(0, R - dR[j]) + rR[j]], f[s][i] - max(0, dR[j] - R) - max(0, dG[j] - G) + rW[j]);
					}
			return ans;
		}
};
