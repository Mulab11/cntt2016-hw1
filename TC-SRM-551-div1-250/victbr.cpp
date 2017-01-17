#include <bits/stdc++.h>

using namespace std;

class ColorfulChocolates{
	public:
		int maximumSpread(string chocolates, int maxSwaps){
			int n = chocolates.size(),ans = 1;
			for (int i = 0;i < n;i++){
				int u = maxSwaps,v = 1;
				for (int j = i-1;j >= 0;j--){
					if (chocolates[j] == chocolates[i]){
						u -= i-j-v;
						v++;
					}
					int w = 1,z = u;
					if (u < 0) break;
					ans = max(ans,v);
					for (int k = i+1;k < n;k++){
						ans = max(ans,w+v-1);
						if (chocolates[k] == chocolates[i]){
							z -= k-i-w;
							w++;
						}		
						if (z < 0) break;				
					}
					if (z>=0) ans = max(ans,w+v-1); 
				}
			}
			return ans;
		}
};