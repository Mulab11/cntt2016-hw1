#include <bits/stdc++.h>
using namespace std;

class NewArenaPassword{
public:
	int f[55], cnt[55][27], n;
	int find(int x){return f[x] != -1 ? (f[x] = find(f[x])) : x;}
	void merge(int u, int v){if(find(u) != find(v)) f[find(u)] = find(v);}
	int minChange(string s, int k){
		int i, j, sum, mx, ans = 0;
		n = s.length();
		memset(f, -1, sizeof(f));
		memset(cnt, 0, sizeof(cnt));
		for(i = 0; i < k; ++ i)
			merge(i, n - k + i);
		for(i = 0; i < n; ++ i)
			++ cnt[find(i)][s[i] - 'a'];
		for(i = 0; i < n; ++ i){
			if(find(i) != i) continue;
			for(j = sum = mx = 0; j < 26; ++ j){
				if(cnt[i][j] > mx) mx = cnt[i][j];
				sum += cnt[i][j];
			} ans += sum - mx;
		} return ans;
	}
};
