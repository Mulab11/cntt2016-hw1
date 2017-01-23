#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
typedef vector <string> vs;
const int MAXN = 305;

class Ear{
public:
	int rx[MAXN], bx[MAXN], by[MAXN], n, m;
	int sf[10005], pf[10005];
	void extract(int &sz, int seq[], vs &s){
		int i; sz = 0;
		for(i = 1; i < int(s.size()); ++ i)
			s[0] += s[i];
		stringstream readin(s[0]);
		while(readin >> seq[++ sz]) ;
		-- sz;
	}
	inline LL f(LL x){return x * (x - 1) / 2;}
	LL getCount(vs rx_, vs bx_, vs by_){
		int i, j, up, dw, fz, fm; LL ans = 0;
		memset(pf, 0, sizeof(pf));
		memset(sf, 0, sizeof(sf));
		extract(n, rx, rx_);
		extract(m, bx, bx_);
		extract(m, by, by_);
		sort(rx + 1, rx + 1 + n);
		for(i = j = 1; i <= 10000; ++ i){ //Preprocess prefix & suffix of red points
			pf[i] = pf[i - 1];
			if(rx[j] == i) ++ pf[i], ++ j;
		}
		for(i = 10000, j = n; i; -- i){
			sf[i] = sf[i + 1];
			if(rx[j] == i) ++ sf[i], -- j;
		}
		for(i = 1; i <= m; ++ i)
			for(j = i + 1; j <= m; ++ j){ //Enumerate the blue points
				fz = bx[i] * (by[i] - by[j]) - by[i] * (bx[i] - bx[j]);
				fm = by[i] - by[j];
				if(fm < 0) fz *= -1, fm *= -1;
				if(fz <= fm || (fz - 1) / fm + 1 > 10000) continue; //Calculate the partition
				if(by[i] > by[j]) up = bx[i], dw = bx[j];
				else up = bx[j], dw = bx[i];
				if(up < dw) ans += ((pf[dw - 1] - pf[up - 1]) * pf[up - 1] + f(pf[up - 1])) * ((sf[dw + 1] - sf[fz / fm + 1]) * sf[fz / fm + 1] + f(sf[fz / fm + 1]));
				else ans += ((pf[dw - 1] - pf[(fz - 1) / fm]) * pf[(fz - 1) / fm] + f(pf[(fz - 1) / fm])) * ((sf[dw + 1] - sf[up + 1]) * sf[up + 1] + f(sf[up + 1]));
			}
		return ans;
	}
};
