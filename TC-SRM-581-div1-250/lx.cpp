#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define bin(x) (1<<(x))
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

class SurveillanceSystem {
public :
	int sum[51], num[51], n;
	vector<int> C[51];
	string getContainerInfo(string A, vector<int> B, int L) {
		n = A.size();
		rep (i, 0, B.size() - 1)  ++num[B[i]];
		rep (i, 1, n) {
			sum[i] = sum[i - 1] + (A[i - 1] == 'X');
		}
		rep (j, L, n) {
			C[sum[j] - sum[j - L]].pb(j);
		}
		string res(n, '-');
		rep (i, 1, n) {
			int flag = 0;
			rep (j, 0, L) if (num[j]) {
				int x = 0;
				rep (k, 0, C[j].size() - 1)
					x += (C[j][k] - L + 1 <= i && i <= C[j][k]);
				if (x + num[j] > C[j].size()) {
					flag = 2;
					break ;
				} else if (x) {
					flag = 1;
				}
			}
			if (flag == 2) 
				res[i - 1] = '+';
			else if (flag == 1) 
				res[i - 1] = '?';
		}
		return res;
	}
};
