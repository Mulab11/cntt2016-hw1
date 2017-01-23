#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55;

class Stamp{
public:
	string goal; int f[MAXN], n;
	int solve(int L){ //Calculate minimal number of pushes for stamp length L
		int i, j; char col;
		memset(f, 0x3f, sizeof(f));
		for(i = L, f[0] = 0; i <= n; ++ i)
			for(j = i, col = 0; j; -- j){
				if(goal[j - 1] != '*'){
					if(col == 0) col = goal[j - 1];
					else if(col != goal[j - 1]) break;
				} if(i - j + 1 < L) continue;
				f[i] = min(f[i], f[j - 1] + (i - j) / L + 1);
			}
		return f[n];
	}
	int getMinimumCost(string goal_, int Lcost, int Pcost){
		int i, ans = 1e8, cur;
		goal = goal_, n = goal.length();
		for(i = 1; i <= n; ++ i){ //Enumerate the length of stamp
			cur = solve(i);
			if(cur <= n) ans = min(ans, i * Lcost + cur * Pcost);
		} return ans;
	}
};
