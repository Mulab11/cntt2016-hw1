#include <bits/stdc++.h>

using namespace std;
const int N = 60;

class TomekPhone{
	public:
		int a[N],b[N],c[N];
		int n,m,ans,tot;
		int minKeystrokes(vector <int> frequencies, vector <int> keySizes){
			ans = 0;tot = 0;memset(a,0,sizeof(a));
			n = frequencies.size();
			m = keySizes.size();
			for (int i = 0;i < n;i++) b[i] = frequencies[i];
			for (int i = 0;i < m;i++) c[i] = keySizes[i];
			sort(b,b+n);
			sort(c,c+m);
			for (int i = 0;i < m;i++) tot += c[i];
			if (tot < n) return -1;
			int t = m-1;
			for (int i = n-1;i >= 0;i--){
				if (a[t] == c[t]) t = m-1;
				a[t]++;ans += b[i]*a[t];
				t--;if (t < 0) t = m-1; 
			}
			return ans;
		}
};
