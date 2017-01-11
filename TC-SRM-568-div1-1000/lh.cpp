#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

namespace Main {
const int maxn = 55;
int n, m, cnt;
int head[maxn], list[maxn<<1], nxt[maxn<<1], cost[maxn<<1], tot;
int pos[maxn][2],num[maxn],use[maxn],lef[maxn],top;
int col[52];
inline void add(int a, int b,int c) {
	tot++;
	nxt[tot] = head[a];
	head[a] = tot;
	list[tot] = b;
	cost[tot] = c;
	return;
}
inline void adde(int a, int b,int c) {
	add(a, b, c);
	add(b, a, c);
	return;
}
bool paint(int a) {
	for (int i = 0; i < n; ++i) if (i != a) {
		if (pos[i][0] < pos[a][0]) {
			if (pos[i][1] > pos[a][0] && pos[i][1] < pos[a][1]) {
				if (!col[i]) {
					col[i] = col[a] ^ 1;
					if (!paint(i)) return false;
				}
				else if (col[i] == col[a]) return false;
			}
		}
		else if (pos[i][0] < pos[a][1] && pos[i][1] > pos[a][1]) {
			if (!col[i]) {
				col[i] = col[a] ^ 1;
				if (!paint(i)) return false;
			}
			else if (col[i] == col[a]) return false;
		}
	}
	return true;
}
inline bool judge1() {
	memset(col, 0, sizeof(col));
	for (int i = 0; i < n; ++i) if (col[i] == 0) {
		col[i] = 2;
		if (!paint(i)) {
			return false;
		}
	}
	return true;
}
inline bool dfs1(int p, int w) {
	if (p >= top) {
		return judge1();
	}
	if (num[use[p]]>=0) return dfs1(p + 1, w);
	num[use[p]] = lef[w];
	pos[lef[w]][0] = use[p];
	for (int i = p + 1; i < top; ++i) {
		if (num[use[i]] == -1) {
			num[use[i]] = lef[w];
			pos[lef[w]][1] = use[i];
			if (dfs1(p + 1, w + 1)) return true;
			num[use[i]] = -1;
			//pos[lef[w]][1] = -1;
		}
	}
	//printf("p=%d\n", p);
	num[use[p]] = -1;
	//pos[lef[w]][0] = -1;
	return false;
}
inline bool solve1() {
	int kk = 0;
	for (int i = 0; i < n; ++i) {
		if (pos[i][0] == -1) {
			lef[kk++] = i;
		}
	}
	//printf("top=%d,kk=%d\n", top, kk);
	return dfs1(0,0);
}
int L[maxn], R[maxn],sum[2];
bool pat(int a) {
	++sum[col[a] - 2];
	for (int i = head[a]; i; i = nxt[i]) {
		int tr = col[a] ^ cost[i];
		if (col[list[i]]) {
			if (col[list[i]] != tr) return false;
		}
		else {
			col[list[i]] = tr;
			if (!pat(list[i])) return false;
		}
	}
	return true;
}
inline bool solve2() {
	int kk = 0,tt=0;
	for (int i = 0; i < n; ++i) if (pos[i][0] >= 0) {
		lef[kk++] = i;
		//printf("%d  %d\n", pos[i][0], pos[i][1]);
	}
	for (int i = 0; i < m; ++i) if (num[i] == -1) {
		num[i] = tt++;
	}
	else num[i] = -1;
	int lft = -1;
	for (int i = 0; i < m; ++i) if (num[i] == -1) L[i] = lft;
	else lft = num[i];

	int lim = 1 << kk;

	for (int sta = 0; sta < lim; ++sta) {
		memset(head, 0, sizeof(head));
		memset(col, 0, sizeof(col));
		tot = 0;
		bool fl = true;
		col[tt - 1] = 2;
		for (int i = 0; i < kk&&fl; ++i)
			for (int j = i + 1; j < kk&&fl; ++j) if (((sta >> i) & 1) == ((sta >> j) & 1)) {
				if (pos[lef[i]][0]<pos[lef[j]][0]){
					if (pos[lef[i]][1] > pos[lef[j]][0] && pos[lef[i]][1] < pos[lef[j]][1]) fl = false;
				}
				else if (pos[lef[i]][0]<pos[lef[j]][1] && pos[lef[i]][1]>pos[lef[j]][1]) fl = false;
			}

		for (int i = 0; i < kk && fl; ++i) if (sta&(1 << i)) {
			if (L[pos[lef[i]][0]] >= 0) adde(L[pos[lef[i]][0]], L[pos[lef[i]][1]], 0);
			else if (L[pos[lef[i]][1]] >= 0) {
				if (col[L[pos[lef[i]][1]]] == 3) fl = false;
				col[L[pos[lef[i]][1]]] = 2;
			}
		}
		else {
			int t = L[pos[lef[i]][1]] - L[pos[lef[i]][0]];
			t &= 1;
			if (L[pos[lef[i]][0]] >= 0) adde(L[pos[lef[i]][0]], L[pos[lef[i]][1]], t);
			else if (L[pos[lef[i]][1]] >= 0) {
				if (col[L[pos[lef[i]][1]]] == ((2 | t)^1)) fl = false;
				col[L[pos[lef[i]][1]]] = 2 | t;
			}
		}
		for (int i = 0; i < tt && fl; ++i) if (col[i]){
			if (!pat(i)) {
				fl = false;
				break;
			}
		}
		for (int i = 0; i < tt && fl; ++i) if (!col[i]) {
			col[i] = 2;
			if (!pat(i)) {
				fl = false;
				break;
			}
		}
		if (fl) {
			return true;
		}
	}
	return false;
}

}

class DisjointSemicircles {
public:
	string getPossibility(vector<int> labels) {
		using namespace Main;
		m = labels.size();
		n = m / 2;
		memset(pos, -1, sizeof(pos));
		for (int i = 0; i < m; ++i) {
			num[i] = labels[i];
			if (num[i] == -1) use[top++] = i;
			else {
				if (pos[num[i]][0] == -1) pos[num[i]][0] = i;
				else pos[num[i]][1] = i;
			}
		}
		if (top <= 14) return solve1() ? "POSSIBLE" : "IMPOSSIBLE";
		else return solve2() ? "POSSIBLE" : "IMPOSSIBLE";
	}
};