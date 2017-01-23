#include <bits/stdc++.h>
using namespace std;

class BigFatInteger{
public:
	int bitCount(int x){
		int ret = 0;
		while(x) ret += x & 1, x >>= 1;
		return ret;
	}
	int calc(int x){
		if(!x) return 0;
		int ret = 0, cnt = 0;
		while(x) ++ ret, cnt += x & 1, x >>= 1;
		if(cnt > 1) ++ ret;
		return ret;
	}
	int minOperations(int a, int b){
		int i, c, ans = 0, mx = 0;
		for(i = 2; i <= a / i; ++ i){
			for(c = 0; a % i == 0; a /= i, ++ c) ;
			if(!c) continue;
			mx = max(mx, calc(b * c));
			++ ans;
		} if(a != 1) ++ ans, mx = max(mx, calc(b));
		return ans + mx;
	}
};
