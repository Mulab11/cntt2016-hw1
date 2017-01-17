#include <bits/stdc++.h>

using namespace std;
const int N = 61;

class ColorfulWolves{
	public:
		int f[N][N];
		int getmin(vector <string> colormap){
			int ans = 0x3f3f3f3f,n = colormap[0].size();
			memset(f,0x3f,sizeof(f));
			for (int i = 0;i < n;i++){
				if (colormap[i][n-1] == 'Y'){
					f[i][1] = 0;
					for (int j = 0;j < n-1;j++)
						if (colormap[i][j] == 'Y') f[i][1]++; 
				}
			}
			for (int i = 2;i < n;i++){
				for (int j = 0;j < n;j++){
					int tot = 0;
					f[j][i] = f[j][i-1];
					for (int k = 0;k < n;k++)
						if (colormap[j][k] == 'Y'){
							f[j][i] = min(f[j][i],f[k][i-1]+tot);
							tot++;
						}
				}
			}
			for (int i = 1;i < n;i++)
				ans = min(ans,f[0][i]);
			if (ans == 0x3f3f3f3f) return -1;
			else return ans;
		}
};
