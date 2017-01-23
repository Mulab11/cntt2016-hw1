#include <bits/stdc++.h>
using namespace std;

class AstronomicalRecords{
public:
	int f[55][55], n, m;
	inline void update(int &a, int b){if(a < b) a = b;}
	int minimalPlanets(vector <int> a, vector <int> b){
		int i, j, k, l, cur, ans = 0;
		n = a.size(), m = b.size();
		memset(f, 0, sizeof(f));
		for(i = 0; i < n; ++ i)
			for(j = 0; j < m; ++ j){
				update(f[i][j], 1);
				update(ans, cur = f[i][j]);
				for(k = i + 1; k < n; ++ k)
					for(l = j + 1; l < m; ++ l)
						if(1LL * a[k] * b[j] == 1LL * b[l] * a[i])
							update(f[k][l], cur + 1);
			}
		return n + m - ans;
	}
};
