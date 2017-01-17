#include <bits/stdc++.h>

using namespace std;
const int N = 60;

class Stamp{
	public:
		int n,ans,f[N];
		int getMinimumCost(string desiredColor, int stampCost, int pushCost){
			ans = 0x7fffffff;
			n = desiredColor.size();
			for (int L = 1;L <= n;L++){
				char c;
				memset(f,0,sizeof(f));
				for (int i = 1;i <= n;i++){
					c = desiredColor[i-1];
					f[i] = 0x3fffffff;
					for (int j = i-1;j >= 0;j--){
						if (i-j >= L && f[j] < 0x3fffffff) f[i] = min(f[i],f[j]+(i-j+L-1)/L);
						if (j == 0) break;
						if (c == '*') c = desiredColor[j-1];
						else if (desiredColor[j-1] != '*' && desiredColor[j-1] != c) break;
					}
				}
				if (f[n] < 0x3fffffff)
				ans = min(ans,L*stampCost+f[n]*pushCost);
			}
			return ans;
		}
};
