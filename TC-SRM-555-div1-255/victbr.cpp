#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 60;

class CuttingBitString{
	public:
		int n,f[N];
		int getmin(string s){
			n = s.size();
			memset(f,0x3f,sizeof(f));
			f[0] = 0;
			for (int i = 1;i <= n;i++){
				ll tot = s[i-1]-'0';
				for (int j =i-1;j >= 0;j--){
					if (check(tot) && s[j] == '1') f[i] = min(f[i],f[j]+1);
					if (j){
						ll u = s[j-1]-'0';
						tot += u << (i-j);
					}
				}
			}
			if (f[n] == 0x3f3f3f3f) f[n] = -1;
			return f[n];
		}
		bool check(ll x){
			while (x && x % 5 == 0) x /= 5;
			return x == 1;
		}
};
