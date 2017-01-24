#include <bits/stdc++.h>

using namespace std;

int n ; 

const int MAXN = 60  ; 

int f[MAXN][MAXN] ; 
class Egalitarianism {
		public:
				int maxDifference(vector<string> mp, int d) {
						n = mp.size();
						memset(f, 0x3f, sizeof f) ; 
						for(int i = 0; i < n; i ++) {
								for(int j = 0; j < n; j ++) if (mp[i][j] == 'Y') j[i[f]] = 1 ; 
								i[i[f]] = 0 ; 
						}
						for (int k = 0; k < n; k ++) for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++) f[i][j] = min(f[i][j], f[i][k] + f[k][j]) ; 
						int mx = 0 ; 
						for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++) mx = max(mx, f[i][j]) ; 
						if (mx < 111111) return mx * d ; 
						return -1 ; 
				}
} sol ;

string x[] = {"NYN",
 "YNY",
 "NYN"} ; 

vector<string> gx ; 

int main() { 
		for (int i = 0; i < 3; i ++) gx.push_back(x[i]) ; 
		printf("%d\n", sol.maxDifference(gx, 10)) ; 
}
