/*
	dsu.
*/

#include <bits/stdc++.h>
using namespace std;

class GooseTattarrattatDiv1 {
	public:
	int sz[233], mx[233], fa[233];
	int gf(int x){return fa[x] == x ? x : fa[x] = gf(fa[x]);}
	int getmin(string S) {
		int n = S.length(), ret = 0;
		memset(sz, 0, sizeof sz);
		for (int i = 0; i < n; ++i) ++sz[S[i]];
		for (int i = 'a'; i <= 'z'; ++i) fa[i] = i, mx[i] = sz[i];
		for (int i = 0; i < n; ++i) if (S[i] != S[n - i - 1]){
			int x = gf(S[i]), y = gf(S[n - i - 1]);
			if (x != y) fa[x] = y, sz[y] += sz[x], mx[y] = max(mx[y], mx[x]);
		}
		for (int i = 'a'; i <= 'z'; ++i) if (fa[i] == i) ret += sz[i] - mx[i];
		return ret;
	}
};

/*
	23333 is a prime number.
*/
