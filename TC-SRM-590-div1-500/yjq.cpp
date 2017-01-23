#include <bits/stdc++.h>
using namespace std;

typedef long long LL ; 

class XorCards {
		public:
				LL numberOfWays(vector<LL> a, LL limit) {
						int n = a.size(); 
					    int i = 0, j = 0 ; 
						for(LL t = 1LL << 62; t; t >>= 1) {
								for(j = i; j < n && !(a[j] & t); j++);
								if(j == n) continue;
								swap(a[i], a[j]);
								for(j = 0; j < n; j ++) {
										if((j != i) && (a[j] & t))
												a[j] ^= a[i];
								}
								i ++;
						}
						LL ans = 0, cur = 0;
						for(i = 0; i < n; i ++) {
								if((cur ^ a[i]) <= limit)
								{
										cur ^= a[i]; 
										ans += 1LL << (n - i - 1); 
								}
						}
						return ans + 1;
				}
} sol ;

int main() { 
		vector<LL> g ; 
		g.push_back(1), g.push_back(2) ; 
		cout << sol.numberOfWays(g, 2) << endl ; 
}
