#include <bits/stdc++.h>
using namespace std;
const int Z = 71;

class DrawingPointsDivOne{
public:
	int pf[285][285], n; bool vis[145][145];
	vector <int> x, y;
	bool check(int m){
		int i, j;
		memset(pf, 0, sizeof(pf));
		for(i = 0; i < n; ++ i){
			++ pf[x[i] + Z][y[i] + Z];
			-- pf[x[i] + Z][y[i] + m + 1 + Z];
			-- pf[x[i] + m + 1 + Z][y[i] + Z];
			++ pf[x[i] + m + 1 + Z][y[i] + m + 1 + Z];
		}
		for(i = 1; i <= 281; ++ i)
			for(j = 1; j <= 281; ++ j)
				pf[i][j] += pf[i][j - 1] + pf[i - 1][j] - pf[i - 1][j - 1];
		for(i = 1; i <= 281; ++ i)
			for(j = 1; j <= 281; ++ j){
				if(pf[i][j]) pf[i][j] = 1;
				pf[i][j] += pf[i][j - 1] + pf[i - 1][j] - pf[i - 1][j - 1];
			}
		for(i = 1; i <= 141; ++ i)
			for(j = 1; j <= 141; ++ j){
				if(vis[i][j]) continue;
				if(pf[i + m][j + m] - pf[i + m][j - 1] - pf[i - 1][j + m] + pf[i - 1][j - 1] == (m + 1) * (m + 1))
					return false;
			}
		return true;
	}
	int maxSteps(vector <int> x_, vector <int> y_){
		int i, l, r, mid;
		x = x_, y = y_, n = x.size();
		memset(vis, false, sizeof(vis));
		for(i = 0; i < n; ++ i)
			vis[x[i] + Z][y[i] + Z] = true;
		for(l = 0, r = 139; l < r; ){ //Check answer for operating mid time(s)
			mid = (l + r + 1) >> 1;
			if(check(mid)) l = mid;
			else r = mid - 1;
		} return r == 139 ? -1 : r;
	}
};
