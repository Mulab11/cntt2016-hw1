#include <bits/stdc++.h>
 
using namespace std;
 
int k, x[15], y[15], axiba, kg,kenji[2222222],good[222222];

class MagicalHats {
public:
  int findMaximumReward(vector <string>, vector <int>, int);
};
int go(int v) {
	if (kenji[v] >= 0) return kenji[v];
	int b[15], vv = v, cur = 0;
	// 分解 
	for (int i=0;i<k;i++) {
		b[i] = vv % 3;
		if (b[i] > 0) cur++;
		vv /= 3;
	}
	if (cur == axiba) {
		kenji[v] = 0;
		for (int i=0;i<k;i++)
			if (b[i] == 1) kenji[v]++;
		return kenji[v];
	}
	// 枚举一个点，先手选最大的，后手在有没有硬币之间选最小的。
	int mx = 0;
	for (int i=0;i<k;i++) {
		if (b[i] > 0) continue;
		int mn = 100000;
		for (int j=1;j<=2;j++) {
			int canbe = 0;
			for (int tt=0;tt<kg;tt++) {
				int t = good[tt];
				int ok = 1;
				for (int z=0;z<k;z++)
				if (b[z] > 0)
				if (t & (1 << z)) {
					if (b[z] == 2) {ok = 0; break; }
				} else {
					if (b[z] == 1) {ok = 0; break; }
				}
				if (!ok) continue;
				if (j == 1) {
					if (t & (1 << i)) {
						canbe = 1;
						break;
					}
				} else {
					if (!(t & (1 << i))) {
						canbe = 1;
						break;
					}
				}
			}
			if (canbe) {
				vv = v;
				int pw = 1;
				for (int z=0;z<i;z++) pw *= 3;
				pw *= j;
				if (go(vv + pw) < mn) mn = go(vv+pw);
			}
		}
		if (mn == 100000) continue;
		if (mn > mx) mx = mn;
	}
	kenji[v] = mx;
	return mx;
}
 
int MagicalHats::findMaximumReward(vector <string> a, vector <int> coins, int axiba) {
	int n = a.size(), m = a[0].length(), i, j, k = 0;
	int row[16], col[16];
	::axiba = axiba;
	for (i=0;i<n;i++)
	for (j=0;j<m;j++)
	if (a[i][j] == 'H') {
		x[k] = i;
		y[k] = j;
		k++;
	}
	::k = k;
	kg = 0;
	// 处理可行状态
	// 和是偶数
	for (int t=0;t<(1<<k);t++) {
		int kq = 0, p[111];
		for (i=0;i<k;i++)
			if (t & (1 << i)) p[kq++] = i;
		if (kq != coins.size()) continue;
		for (i=0;i<n;i++) row[i] = 0;
		for (i=0;i<m;i++) col[i] = 0;
		for (i=0;i<n;i++)
		for (j=0;j<m;j++)
			if (a[i][j] == 'H') {
				row[i] ^= 1;
				col[j] ^= 1;
			}
		for (i=0;i<kq;i++) {
		  row[x[p[i]]] ^= 1;
		  col[y[p[i]]] ^= 1;
		}
		int ok = 1;
		for (i=0;i<n;i++)
			if (row[i]) ok = 0;
		for (i=0;i<m;i++)
			if (col[i]) ok = 0;
		if (!ok) continue;
		good[kg++] = t;
	}
	if (kg == 0) return -1;
	// 处理三进制状态 
	int pw = 1;
	for (i=0;i<k;i++) pw *= 3;
	for (i=0;i<pw;i++) kenji[i] = -1;
	int cnt = go(0);
	sort(coins.begin(),coins.end());
	int ans = 0;
	// 取走最小的若干个硬币
	for (i=0;i<cnt;i++) ans += coins[i];
	return ans;
}