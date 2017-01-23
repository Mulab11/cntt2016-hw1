#include <bits/stdc++.h>
using namespace std;
const int BOUND = 17;

class FlippingBitsDiv1{
public:
	bitset <300> pf[305]; string s;
	int n, m, f[305], g[305], c0[305], c1[305];
	int solve1(){
		int c = (n - 1) / m + 1, i, C = 1 << c;
		int j, k, c0, c1, ret = n, nowAns, ext;
		bitset <300> S, cur;
		for(i = 0; i < n; ++ i){
			S[i] = bool(s[i] - '0');
			if(i) pf[i] = pf[i - 1];
			pf[i][i] = !pf[i][i];
		}
		for(i = 0; i < C; ++ i){
			cur = S;
			for(j = ext = 0; j < c; ++ j)
				if(i & (1 << j))
					++ ext, cur ^= pf[min((j + 1) * m, n) - 1];
			for(j = nowAns = 0; j < m; ++ j){
				for(k = j, c0 = c1 = 0; k < n; k += m)
					if(cur[k]) ++ c1;
					else ++ c0;
				nowAns += min(c0, c1);
			} ret = min(ret, nowAns + ext);
		} return ret;
	}
	int solve2(){
		int i, M = 1 << m, j, k, ret = n, l;
		for(i = 0; i < M; ++ i){
			for(j = l = 0; j < n; j += m, ++ l){
				c0[l] = c1[l] = 0;
				for(k = 0; k < m && j + k < n; ++ k)
					if(bool(i & (1 << k)) != bool(s[j + k] - '0'))
						++ c1[l];
					else ++ c0[l];
			}
			f[0] = c1[0], g[0] = c0[0] + 1;
			for(j = 1; j < (n - 1) / m + 1; ++ j){
				f[j] = min(f[j - 1] + c1[j], g[j - 1] + c1[j]);
				g[j] = min(g[j - 1] + c0[j], f[j - 1] + c0[j] + 2);
			} ret = min(ret, min(f[(n - 1) / m], g[(n - 1) / m]));
		} return ret;
	}
	int getmin(vector <string> S, int m_){
		for(int i = 0; i < int(S.size()); ++ i)
			s += S[i];
		n = s.length(), m = m_;
		if((n - 1) / m + 1 <= BOUND) return solve1();
		return solve2();
	}
};
