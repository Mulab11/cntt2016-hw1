/*
	Implementation
	dsu, brute force
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 23333;
const LL MOD = 1000000007;
class GooseInZooDivOne {
	public:
	int r, c;
	int fa[MAXN], sz[MAXN]; // dsu
	int getf(int x){return fa[x] == x ? x : fa[x] = getf(fa[x]);} // dsu
	int getid(int r0, int c0){return r0 * c + c0;}
	int count(vector <string> field, int dist) {
		r = field.size(); c = field[0].length();
		for (int i = 0; i < r * c; ++i) fa[i] = i, sz[i] = 1; // init
		for (int i = 0; i < r; ++i) for (int j = 0; j < c; ++j) if (field[i][j] == 'v') // bird A
			for (int i1 = 0; i1 < r; ++i1) for (int j1 = 0; j1 < c; ++j1) // bird B
				if ((i != i1 || j != j1) && field[i1][j1] == 'v' && abs(i - i1) + abs(j - j1) <= dist){ // if (distance(A, B) <= dist)
					int x = getf(getid(i, j)), y = getf(getid(i1, j1));
					if (x != y) fa[x] = y, sz[y] += sz[x], printf("%d %d %d %d, sz = %d\n", i, j, i1, j1, sz[y]); // merge(A, B)
				}
		// answer = 2 ^ (cnt_odd - 1 + cnt_even) - 1
		int cnt1 = 0, cnt2 = 0;
		for (int i = 0; i < r; ++i) for (int j = 0; j < c; ++j) if (field[i][j] == 'v'){ // count odd / even sizes
			int id = getid(i, j);
			if (fa[id] == id) ++(sz[id] & 1 ? cnt1 : cnt2);
		}
		printf("%d %d\n", cnt1, cnt2);
		if (cnt1) --cnt1;
		cnt1 += cnt2;
		LL ans = 1;
		for (int i = 0; i < cnt1; ++i) ans = ans * 2 % MOD; 
		if (--ans < 0) ans += MOD;
		return ans;
	}
};

/*
	Anger, Stress and secrets
	they Won't break you
	Wake up
	Put aside- you're
	Feeling nothing,
	Freely Speed up,
	Landing, Stepping, Jumping, Jumper.
		- Jumper
*/
