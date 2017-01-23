#include <bits/stdc++.h>

using namespace std;

typedef long long LL ;

vector<LL> a ; 

class XorAndSum {
		public:
				LL maxSum(vector<LL> number) {
						a = number;
						int n = number.size() ; 
						for(LL k = (1ll << 60),i = 0;k && i < n;k >>= 1) {
								for(int j = i;j < n;j ++) if (a[j] & k) {swap(a[i],a[j]);break;}
								if (!(a[i] & k)) continue;
								for(int j = 0;j < n;j ++)
										if ((j != i) && (a[j] & k)) a[j] ^= a[i];
								i ++ ; 
						}
						for(int i = 1;i < n;i ++) a[0] ^= a[i]; 
						LL ans = a[0];
						for(int i = 1;i < n;i ++) ans += (a[i] ^ a[0]) ; 
						return ans;
				}
} sol ;

int main() { 
}
