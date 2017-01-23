#include <bits/stdc++.h>
using namespace std;

class SpellCards{
public:
	int maxDamage(vector <int> sz, vector <int> val){
		int n = sz.size(), i, j, f[55];
		memset(f, 0, sizeof(f));
		for(i = 0; i < n; ++ i) //0-1 knapsack
			for(j = n; j >= sz[i]; -- j)
				if(f[j] < f[j - sz[i]] + val[i])
					f[j] = f[j - sz[i]] + val[i];
		return f[n];
	}
};
