#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55;

class GooseTattarrattatDiv1{
public:
	int n, f[MAXN], cnt[MAXN][26];
	int find(int x){return f[x] < 0 ? x : (f[x] = find(f[x]));}
	void merge(int u, int v){
		u = find(u), v = find(v);
		if(u == v) return;
		if(f[u] > f[v]) swap(u, v);
		f[u] += f[v], f[v] = u;
	}
	int getmin(string s){
		int i, j, ans = 0, mx;
		memset(f, -1, sizeof(f));
		n = s.length();
		for(i = 0; i < n / 2; ++ i)
			merge(i, n - i - 1);
		for(i = 0; i < n; ++ i)
			for(j = i + 1; j < n; ++ j)
				if(s[i] == s[j])
					merge(i, j);
		for(i = 0; i < n; ++ i)
			++ cnt[find(i)][s[i] - 'a'];
		for(i = 0; i < n; ++ i){
			if(find(i) != i) continue;
			for(j = mx = 0; j < 26; ++ j)
				if(cnt[i][j] > mx)
					mx = cnt[i][j];
			ans += - f[i] - mx;
		} return ans;
	}
};
