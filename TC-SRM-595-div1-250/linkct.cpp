#include <bits/stdc++.h>
using namespace std;

class LittleElephantAndIntervalsDiv1{
public:
	int m, col[1005]; bool vis[55];
	long long int getNumber(int n, vector <int> l, vector <int> r){
		int i, j, ans = 0; m = l.size();
		memset(col, 0, sizeof(col));
		for(i = 0; i < m; ++ i)
			for(j = l[i]; j <= r[i]; ++ j)
				col[j] = i + 1;
		memset(vis, false, sizeof(vis));
		for(i = 1; i <= n; ++ i)
			vis[col[i]] = true;
		for(i = 1; i <= m; ++ i)
			if(vis[i]) ++ ans;
		return 1LL << ans;
	}
};
