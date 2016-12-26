#include <bits/stdc++.h>

using namespace std;

#define For(i,l,h) for(int i=(l);i<=(h);++i)

typedef vector<string> vs;
typedef vector<double> vd;
typedef long long ll;

const int mod = 555555555;
const int fafafa = 3200;

int axiba[fafafa][fafafa];

inline void inc(int& x, int y) {if((x+=y)>=mod)x-=mod;}

struct XorBoard{
	int count(int h,int w,int rc,int cc,int s){
		For (i, 0, fafafa - 1) {
			axiba[i][0] = axiba[i][i] = 1;
			For (j, 1, i - 1)
				axiba[i][j] = (axiba[i - 1][j - 1] + axiba[i - 1][j]) % mod;
		}
		int xjbxjb = 0;
		For (i, 0, min(rc, h))
		For (j, 0, min(cc, w))
		if (i * w + j * h - 2 * i * j == s) 
			inc (xjbxjb, solve(i, j, rc, cc, h, w));
		return xjbxjb;
	}
	int solve(int rt, int ct, int rtot, int ctot, int h, int w) {
		int Rllll = rtot - rt, Cllll = ctot - ct;
		if ((Rllll & 1) || (Cllll & 1)) return 0;
		Rllll >>= 1; Cllll >>= 1;
		ll res = 1;
		res = (res * axiba[h][rt] % mod) * axiba[w][ct] % mod;
		res = (res * axiba[h + Rllll - 1][h - 1] % mod) * axiba[w + Cllll - 1][w - 1] % mod;
		return res;
	}
}; 