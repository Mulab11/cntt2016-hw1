#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;

class TrafficCongestion{
public:
	int f[1000005];
	int theMinCars(int h){
		if(!h) return 1;
		f[0] = 1, f[1] = 2;
		for(int i = 2; i <= h; ++ i)
			f[i] = (f[i - 1] + (f[i - 2] * 2 + 1) % MOD) % MOD;
		return (f[h] - f[h - 1] + MOD) % MOD;
	}
};
