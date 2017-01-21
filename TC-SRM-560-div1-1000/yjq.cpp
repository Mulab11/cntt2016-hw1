#include <bits/stdc++.h>

using namespace std;

typedef double _float ; 

const int MAXN = 15 ; 
const _float eps = 1e-8 ; 

bool use[MAXN][MAXN];

void check(vector<string> a) {
		string tmp = "";
		for(int i = 0;i < a.size();i ++) tmp = tmp + a[i];
		for(int i = 0;i < tmp.length();i += 3) {
				int u = tmp[i] - 'a',v = tmp[i + 1] - 'a';
				use[u][v] = use[v][u] = 1;
		}
}


_float V[MAXN] ; 

_float a[MAXN];

class BoundedOptimization {
		public:

				_float maxValue(vector <string> str, vector <int> lb, vector <int> ub, int mx) {
						int n = lb.size();
						check(str);
						_float ans = 0;
						int N = (1 << n) - 1;
						for(int s = 0;s < (1 << n);s ++) {
								bool cliq = 1;
								for(int i = 0;i < n;i ++)
										if (s & (1 << i))
												for(int j = 0;j < n;j ++)
														if (i != j && (s & (1 << j)) && !use[i][j]) {cliq = 0;break;}
								if (!cliq) continue;
								for(int tmp = N ^ s;;tmp = (N ^ s) & (tmp - 1)) {
										_float m = mx;
										for(int i = 0;i < n;i ++)
												if (!(s & (1 << i))) {
														if (tmp & (1 << i)) V[i] = ub[i]; 
														else V[i] = lb[i];
														m -= V[i];
												}
										if (m < 0) continue;
										_float lm = m;
										for(int i = 0;i < n;i ++)
												if (s & (1 << i)) {
														a[i] = 0;
														for(int j = 0;j < n;j ++)
																if (!(s & (1 << j)) && use[i][j]) a[i] += V[j];
														V[i] = a[i] + m / 2;
														lm -= m / 2 + a[i];
												}
										bool flag = 1;
										for(int i = 0;i < n;i ++)
												if (s & (1 << i)) {
														V[i] += lm / (__builtin_popcount(s));
														if (V[i] > ub[i] + eps || V[i] < lb[i] - eps) flag = 0; 
												}
										if (!flag) {
												if (!tmp) break;
												continue;
										}
										_float cur = 0;
										for(int i = 0;i < n;i ++) for(int j = i + 1;j < n;j ++) if (use[i][j]) cur += V[i] * V[j]; 
										ans = max(ans,cur);
										if (!tmp) break;
								}
						}
						return ans;
				}
};
