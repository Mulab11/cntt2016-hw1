#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int MAXN = 55;

class CuttingBitString{
public:
	int f[MAXN], n;
	int getmin(string str){
		int i, j, k; LL sum;
		n = str.length();
		for(i = 1, f[0] = 0; i <= n; ++ i){
			f[i] = n + 1;
			for(j = 1; j <= i; ++ j){
				if(str[j - 1] == '0') continue;
				for(k = j, sum = 0; k <= i; ++ k)
					sum = (sum << 1LL) | (str[k - 1] - '0');
				while((sum != 1LL) && ((sum % 5LL) == 0LL)) sum /= 5LL;
				if(sum == 1LL) f[i] = min(f[i], f[j - 1] + 1);
			}
		} return f[n] == n + 1 ? -1 : f[n];
	}
};
