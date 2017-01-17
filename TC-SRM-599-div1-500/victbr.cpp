#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
/*
根据pick定理，格点三角形满足s=a+b/2-1， 
看到 
*/

class FindPolygons{
	public:
		int ans;
		double minimumPolygon(int L){
			if (L<3) return -1;
			if (L&1) return -1;
			ans = 0x7fffffff;
			for (int i = 1;i <= L;i++)
				for (int j = i;j <= L-i-j;j++){
					int k = L-i-j;
					if (i+j <= k) continue;
					ll s = (ll)(i+j+k)*(i+j-k)*(i-j+k)*(-i+j+k);
					if (s % 4) continue;s /= 4;
				//	if(i == 3 && j == 4 && k == 5) cout << s << endl;
					ll t = sqrt(s)+0.5;
					if (t*t == s) ans = min(ans,k-i);
				}
			if (ans != 0x7fffffff) return ans;
			if (L%4 == 0) return 0;
			return 1;
		}
};
