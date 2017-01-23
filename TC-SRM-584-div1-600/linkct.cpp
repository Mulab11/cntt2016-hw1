#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int MAXN = 55;

class Excavations{
public:
	LL f[MAXN], g[MAXN], C[MAXN][MAXN];
	int cnt[MAXN][MAXN], available[MAXN], n;
	LL count(vector <int> type, vector <int> depth, vector <int> found, int m){
		int i, j, k, l; LL f_, g_, ans = 0LL;
		vector <int> tmp, tmp_; n = type.size();
		memset(C, 0, sizeof(C));
		for(i = 0; i <= n; ++ i)
			for(C[i][0] = j = 1; j <= i; ++ j)
				C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
		tmp = depth, tmp_ = type;
		sort(tmp.begin(), tmp.end());
		sort(tmp_.begin(), tmp_.end());
		memset(cnt, 0, sizeof(cnt));
		for(i = 0; i < n; ++ i){
			depth[i] = lower_bound(tmp.begin(), tmp.end(), depth[i]) - tmp.begin() + 1;
			type[i] = lower_bound(tmp_.begin(), tmp_.end(), type[i]) - tmp_.begin() + 1;
			++ cnt[depth[i]][type[i]];
			++ cnt[depth[i]][0];
		}
		for(i = 0; i < int(found.size()); ++ i)
			found[i] = lower_bound(tmp_.begin(), tmp_.end(), found[i]) - tmp_.begin() + 1;
		memset(available, 0, sizeof(available));
		for(i = 1; i <= n; ++ i){
			if(!cnt[i][0]) continue;
			//Calculate all solutions available at D = i but not D < i
			for(j = 0; j <= n; ++ j)
				available[j] += cnt[i][j];
			memset(f, 0, sizeof(f));
			memset(g, 0, sizeof(g));
			f[0] = 1;
			for(j = 0; j < int(found.size()); ++ j)
				for(k = m; k >= 0; -- k){
					f_ = g_ = 0;
					for(l = 1; l <= available[found[j]] && l <= k; ++ l){
						//Case 1: g -> g, choose arbitrarily
						g_ += g[k - l] * C[available[found[j]]][l];
						//Case 2: f -> g, choose latest only
						g_ += f[k - l] * C[cnt[i][found[j]]][l];
						//Case 3: f -> f, choose not latest only
						f_ += f[k - l] * (C[available[found[j]]][l] - C[cnt[i][found[j]]][l]);
					} f[k] = f_, g[k] = g_;
				}
			for(j = found.size(); j <= m; ++ j)
				ans += g[j] * C[n - available[0]][m - j];
		} return ans;
	}
};
