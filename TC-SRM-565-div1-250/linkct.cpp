#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int MAXN = 55;

class MonstersValley{
public:
	int n; LL f[MAXN][MAXN * 2];
	inline void update(LL &a, LL b){if(a < b) a = b;}
	int minimumPrice(vector <LL> dread, vector <int> price){
		//f[i][j]: Consider the first i monsters, current damage taken is j, maximal value = f[i][j]
		int i, j;
		memset(f, -1, sizeof(f));
		n = dread.size();
		f[0][0] = 0LL;
		for(i = 0; i < n; ++ i)
			for(j = 0; j <= 2 * i; ++ j)
				if(~f[i][j]){
					if(f[i][j] >= dread[i]) update(f[i + 1][j], f[i][j]);
					update(f[i + 1][j + price[i]], f[i][j] + dread[i]);
				}
		for(i = 0; f[n][i] == -1; ++ i) ;
		return i;
	}
};
