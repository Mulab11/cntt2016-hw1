#include <bits/stdc++.h>

using namespace std;
const int N = 60;

class SpellCards{
	public:
		int n;
		int f[N][N];
		int maxDamage(vector <int> level, vector <int> damage){
			n = level.size();
			for (int i = 0;i < n;i++)
				for (int j = 0;j <= n-level[i];j++)
					f[i][j+level[i]] = max(f[i-1][j]+damage[i],f[i][j+level[i]]);
			return f[n-1][n];
		}
};
