#include <bits/stdc++.h>
using namespace std;
const int MAXN = 25, MAXS = 1355;

class RandomPaintingOnABoard{
public:
	int p[MAXN][MAXN], n, m, remain[MAXN];
	int f[MAXS], g[MAXS], sum; double cof[MAXS];
	double solve(int st){
		int i, j, tot = 0, sgn = 0, f_, g_, ub;
		double ret = 0.0;
		memset(remain, 0, sizeof(remain));
		for(i = 0; i < n; ++ i){
			if(st & (1 << i))
				for(j = 0, sgn ^= 1; j < m; ++ j)
					tot += p[i][j];
			else for(j = 0; j < m; ++ j)
				remain[j] += p[i][j];
		}
		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(g));
		if(sgn) g[0] = f[remain[0]] = 1;
		else f[0] = g[remain[0]] = 1;
		for(i = 1, ub = remain[0]; i < m; ++ i)
			for(j = (ub += remain[i]); j >= 0; -- j){
				f_ = f[j], g_ = g[j];
				if(j >= remain[i]){
					f_ += g[j - remain[i]];
					g_ += f[j - remain[i]];
				} f[j] = f_, g[j] = g_;
			}
		for(i = 0; i <= ub; ++ i)
			ret += (g[i] - f[i]) * cof[sum - (tot + i)];
		return ret;
	}
	double expectedSteps(vector <string> prob){
		int i, j, N; double ans = 0.0, tmp; sum = 0;
		n = prob.size(), m = prob[0].length();
		if(n > m){
			for(i = 0; i < n; ++ i)
				for(j = 0; j < m; ++ j)
					sum += (p[j][i] = prob[i][j] - '0');
			swap(n, m);
		}else{
			for(i = 0; i < n; ++ i)
				for(j = 0; j < m; ++ j)
					sum += (p[i][j] = prob[i][j] - '0');
		}
		for(i = 0; i < sum; ++ i){
			tmp = i * 1.0 / sum;
			cof[i] = tmp / (1.0 - tmp);
		} cof[sum] = 0.0;
		for(i = 0, N = (1 << n); i < N; ++ i)
			ans += solve(i);
		return ans + 1.0;
	}
};
