#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;

class XorCards{
public:
	int n; LL base[55], tmp[55];
	void add(LL x){
		for(int i = 0; i <= n; ++ i){
			if((x & (1LL << i)) == 0) continue;
			if(base[i]) x ^= base[i];
			else{base[i] = x; break;}
		}
	}
	LL add_(LL x){
		int i; LL ret = 1LL << n;
		memcpy(tmp, base, sizeof(base));
		for(i = 0; i <= n; ++ i){
			if((x & (1LL << i)) == 0) continue;
			if(tmp[i]) x ^= tmp[i];
			else{tmp[i] = x; break;}
		} if(tmp[n]) return 0LL;
		for(i = 0; i < n; ++ i)
			if(tmp[i]) ret >>= 1;
		return ret;
	}
	LL numberOfWays(vector <LL> seq, LL limit){
		int i, j; LL ans = 0LL, cur;
		n = seq.size();
		memset(base, 0, sizeof(base));
		for(i = 49; i >= 0; -- i){
			for(j = cur = 0; j < n; ++ j)
				if(seq[j] & (1LL << i))
					cur |= 1LL << j;
			if(limit & (1LL << i)){
				ans += add_(cur);
				add(cur | (1LL << n));
			}else add(cur);
		} if(base[n]) return ans;
		for(i = j = 0; i < n; ++ i)
			if(base[i]) ++ j;
		return ans + (1LL << (n - j));
	}
};
