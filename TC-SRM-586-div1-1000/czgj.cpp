/*
	Big dp
	not so *BIG* though
*/
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int oo = 0x3f3f3f3f;
const int SS = 30;
int a0[SS][SS], a1[SS][SS], (*f)[SS] = a0, (*g)[SS] = a1;
int sum(int l, int r){return (l + r) * (r - l + 1) / 2;}
void cmin(int &a, int b){a = min(a, b);}
class StringWeight {
	public:
	int getMinimum(vector <int> L) {
		int n = L.size(); vector<int> S(n + 1);
		rep(i, 1, n) S[i] = S[i - 1] + L[i - 1];
		memset(a0, 0x3f, sizeof a0);
		memset(a1, 0x3f, sizeof a0);
		f[0][0] = 0;
		rep(T, 0, n - 1){
			memset(g, 0x3f, sizeof a0);
			rep(i, 0, 26) rep(j, 0, 26){ // i = started(not ended), j = ended
				if (f[i][j] == oo) continue;
				int t = min(26, L[T]); // alphabets in this part
				if (j + t > 26) continue;
				rep(ti, 0, 26) rep(tj, 0, 26){
					if (ti > i || i + j + tj > 26 || ti + tj > t) continue;
					int v = f[i][j] + sum(S[T] + 1, S[T] + ti) - sum(S[T + 1] - tj + 1, S[T + 1]);
					if (i == ti) v += L[T] - t, cmin(g[i - ti + tj][j + t - tj], v); // extra cost
					else cmin(g[i - ti + tj][j + ti + max(t - i - tj, 0)], v); // free cells can be filled with started ones, no extra cost
				}
			}
			swap(f, g);
		}
		int ret = oo;
		rep(i, 0, 26) cmin(ret, f[0][i]);
		return ret;
	}
};

/*
	Sandanjuu to Telecaster
		- Unhappy Refrain 
*/
