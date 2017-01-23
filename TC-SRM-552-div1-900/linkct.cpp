#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int MAXP = 1000005;

class HolyNumbers{
public:
	int P[MAXP], pcnt; bool isComp[MAXP];
	LL solve(int id, LL n){
		if(id > pcnt || P[id] > n) return 1LL;
		if(LL(P[id]) * P[id] > n){
			if(n >= P[pcnt]) return pcnt - id + 2;
			return upper_bound(P + 1, P + 1 + pcnt, int(n)) - P - id + 1;
		}
		LL ret = solve(id + 1, n), i, P_ = LL(P[id]) * P[id];
		for(i = P[id]; i <= n; i *= P_)
			ret += solve(id + 1, n / i);
		return ret;
	}
	LL count(LL n, int p){
		if(p == 1) return 1LL;
		int i, j, tmp;
		for(i = 2; i <= p; ++ i){
			if(!isComp[i]) P[++ pcnt] = i;
			for(j = 1; (tmp = i * P[j]) <= p; ++ j){
				isComp[tmp] = true;
				if(i % P[j] == 0) break;
			}
		} return solve(1, n);
	}
};
