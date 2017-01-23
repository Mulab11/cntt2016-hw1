#include <cstdio>
#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const LL MOD = 1000000007LL;
const int MAXS = 85;

class ConversionMachine{
	public:
		int n, tmp[MAXS][MAXS], tr[MAXS][MAXS], res[MAXS][MAXS];
		int id[13][13], st; vector <LL> cost; LL maxCost;
		void mul(int x[MAXS][MAXS], const int y[MAXS][MAXS]){
			int i, j, k;
			memset(tmp, 0, sizeof(tmp));
			for(i = 0; i <= st; ++ i)
				for(j = 0; j <= st; ++ j)
					for(k = 0; k <= st; ++ k)
						tmp[i][j] = (LL(x[i][k]) * y[k][j] + tmp[i][j]) % MOD;
			memcpy(x, tmp, sizeof(tmp));
		}
		int countAll(string A, string B, vector <int> cost_, int maxCost_){
			int i, j, k, ID, c1, c2; LL step; cost.clear();
			for(i = 0; i < 3; ++ i) cost.push_back(LL(cost_[i]));
			maxCost = maxCost_, n = A.length();
			for(i = st = 0; i <= n; ++ i)
				for(j = 0; i + j <= n; ++ j)
					id[i][j] = st ++;
			for(i = 0; i <= n; ++ i) //Construct the transforming matrix
				for(j = 0; i + j <= n; ++ j){
					k = n - i - j, ID = id[i][j];
					if(i) tr[id[i - 1][j + 1]][ID] = i;
					if(j) tr[id[i][j - 1]][ID] = j;
					if(k) tr[id[i + 1][j]][ID] = k;
				}
			tr[st][id[0][0]] = tr[st][st] = 1;
			for(i = c1 = c2 = 0; i < n; ++ i)
				if(((A[i] - 'a' + 1) % 3) + 'a' == B[i])
					maxCost -= cost[A[i] - 'a'], ++ c1;
				else if(((A[i] - 'a' + 2) % 3) + 'a' == B[i])
					maxCost -= cost[A[i] - 'a'] + cost[(A[i] - 'a' + 1) % 3], ++ c2;
			if(maxCost < 0LL) return 0;
			step = c1 + c2 * 2 + maxCost / (cost[0] + cost[1] + cost[2]) * 3 + 1;
			memset(res, 0, sizeof(res));
			for(i = 0; i <= st; ++ i) res[i][i] = 1;
			while(step){
				if(step & 1LL) mul(res, tr);
				mul(tr, tr);
				step >>= 1;
			} return res[st][id[c2][c1]];
		}
};
