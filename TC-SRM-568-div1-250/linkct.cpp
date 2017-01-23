#include <bits/stdc++.h>
using namespace std;
typedef vector <int> vi;

class BallsSeparating{
public:
	int minOperations(vi r, vi g, vi b){
		int i, j, k, l, ans = 1e9, cur, n;
		n = r.size(); if(n < 3) return -1;
		for(i = 0; i < n; ++ i)
			for(j = i + 1; j < n; ++ j)
				for(k = j + 1; k < n; ++ k){ //Enumerate places for red, green and blue balls
					for(l = cur = 0; l < n; ++ l)
						if(l == i) cur += g[l] + b[l];
						else if(l == j) cur += r[l] + b[l];
						else if(l == k) cur += r[l] + g[l];
						else cur += r[l] + g[l] + b[l] - max(r[l], max(g[l], b[l]));
					ans = min(ans, cur);
				}
		return ans;
	}
};
