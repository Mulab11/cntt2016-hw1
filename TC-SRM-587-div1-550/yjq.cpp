#include <bits/stdc++.h>

using namespace std;

const int MAXN = 70010 ; 

double f[MAXN], g[MAXN] ;  
class TriangleXor {
		public:
				int theArea(int w) {
						double ans = 0.0;
						for(int i = 0; i <= w; i++) {
								f[i] = g[i] = 1.0 * w / (w * 2 - i) * (i + 1); 
								if(i) f[i] -= g[i - 1] * 2.0;
								if(i - 1) f[i] += g[i - 2];
								if(!((w - i) & 1)) ans += f[i];
						}
						return (int)(ans * w / 2.0);
				}
} sol ;

int main() { 
		printf("%d\n", sol.theArea(12345)) ; 
}
