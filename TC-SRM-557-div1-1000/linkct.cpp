#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;

class XorAndSum{
public:
	LL base[55]; int n;
	LL maxSum(vector <LL> seq){
		int i, j; LL ret = 0LL;
		memset(base, 0, sizeof(base));
		n = seq.size();
		for(i = 0; i < n; ++ i)
			for(j = 49; j >= 0; -- j){ //Build the linear base using every number
				if((seq[i] & (1LL << j)) == 0) continue;
				if(base[j]) seq[i] ^= base[j];
				else{base[j] = seq[i]; break;}
			}
		for(i = 0; i <= 49; ++ i){ //Clear extra bits
			if(!base[i]) continue;
			for(j = i + 1; j <= 49; ++ j)
				if(base[j] & (1LL << i))
					base[j] ^= base[i];
		}
		for(i = j = 49; i >= 0; -- i)
			if(base[i]) base[j --] = base[i];
		for(i = 48; i > j; -- i)
			base[49] ^= base[i];
		for(i = 48; i > j; -- i)
			ret += base[i] ^ base[49];
		return ret + (n - 48 + j) * base[49];
	}
};
