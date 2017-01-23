#include <bits/stdc++.h>
using namespace std;

class ICPCBalloons{
public:
	vector <int> mc, lc, mn, ln;
	int solve(vector <int> &pv, vector <int> &nd){
		int i, j, sum = 0, ans = 0;
		for(i = 0; i < int(pv.size()); ++ i) sum += pv[i];
		for(i = 0; i < int(nd.size()); ++ i) sum -= nd[i];
		if(sum < 0) return 5000;
		for(i = int(nd.size()) - 1, j = int(pv.size()) - 1; i >= 0; -- i)
			if(j >= 0) ans += max(nd[i] - pv[j --], 0);
			else ans += nd[i];
		return ans;
	}
	int minRepaintings(vector <int> bc, string bs, vector <int> ac){
		int n, m, i, j, ans = 5000;
		n = bs.length(), m = ac.size();
		mc.clear(); lc.clear();
		for(i = 0; i < n; ++ i)
			if(bs[i] == 'M') mc.push_back(bc[i]);
			else lc.push_back(bc[i]);
		sort(mc.begin(), mc.end());
		sort(lc.begin(), lc.end());
		sort(ac.begin(), ac.end());
		for(i = 0; i < (1 << m); ++ i){
			mn.clear(); ln.clear();
			for(j = 0; j < m; ++ j)
				if(i & (1 << j)) mn.push_back(ac[j]);
				else ln.push_back(ac[j]);
			ans = min(ans, solve(mc, mn) + solve(lc, ln));
		} return ans == 5000 ? -1 : ans;
	}
};
