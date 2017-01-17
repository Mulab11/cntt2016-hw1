#include <bits/stdc++.h>

using namespace std;
const int N = 60;

class BallsSeparating{
	public:
		int n,f[N][8];
		int minOperations(vector <int> red, vector <int> green, vector <int> blue){
			n = red.size();
			if (n < 3) return -1;
			memset(f,0x3f,sizeof(f));
			f[0][0] = 0;
			for (int i = 1;i <= n;i++){
				for (int j = 0;j < 8;j++){
					f[i][j|1] = min(f[i][j|1],f[i-1][j]+red[i-1]+green[i-1]);
					f[i][j|2] = min(f[i][j|2],f[i-1][j]+blue[i-1]+green[i-1]);
					f[i][j|4] = min(f[i][j|4],f[i-1][j]+red[i-1]+blue[i-1]);
				}
			}
			return f[n][7];
		}
};
