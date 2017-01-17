#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 101000;

class HolyNumbers{ 
	public:
		bool bo[N*10];
		int prime[N],len;
		long long count(long long upTo, int maximalPrime){
			make_prime(maximalPrime);
			return dfs(upTo,1);
		}
		void make_prime(int p){	
			for (int i = 2;i <= p;i++){
				if (!bo[i]) prime[++len] = i;
				for (int j = 1;j <= len && i*prime[j] <= p;j++){
					bo[i*prime[j]] = 1;
					if (i%prime[j] == 0) break;
				}
			}
		}
		long long dfs(ll x,int y){
			if (x < prime[y]) return 1;
			if (y > len) return 1;
			if (x < (ll)prime[y]*prime[y])
				return upper_bound(prime + y,prime + len + 1,x) - (prime + y) + 1;
			
			
			ll tot = 0,z = prime[y];z = z * z;
			for (ll o = x/prime[y];o;o /= z)
				tot += dfs(o,y+1);
			tot += dfs(x,y+1);
			return tot;
		}
};
