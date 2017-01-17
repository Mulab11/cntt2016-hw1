#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 3010,mod = 555555555;

class XorBoard{
	public:
		int ans,f[N][N];
		int count(int H, int W, int Rcount, int Ccount, int S){
			ans = 0;
			
			memset(f,0,sizeof(f));
			f[0][0] = 1;
			for (int i = 1;i <= 3000;i++){
				f[i][0] = 1;
				for (int j = 1;j <= i;j++)
					f[i][j] = add(f[i-1][j],f[i-1][j-1]);
			}
			
			for (int x = 0;x <= H;x++){
				int y = S - x*W;
//				if (x == 777) cout <<  << endl;
				if (H-x*2 != 0) if (y % (H - x*2)) continue;
				if (H-x*2 == 0 && y != 0) continue;
				if (H - x*2) y /= H - x*2;
				if (y > W) continue;
				if ((Rcount - x)%2) continue;
				if(y || H-x*2) if ((Ccount - y)%2) continue;//
				if (x > Rcount) continue;
				if (y > Ccount) continue;
				if (y < 0) continue;
				
				if (y == 0 && H-x*2 == 0){
					
					for (int y = 0;y <= min(Ccount,W);y++) 
						if ((Ccount-y)%2 == 0){
							ans = add(ans,(ll)C((Rcount-x)/2+H-1,H-1)*C((Ccount-y)/2+W-1,W-1)%mod*C(H,x)%mod*C(W,y)%mod);
							cout << x<<' ' <<y << endl;
						}
				}
				else ans = add(ans,(ll)C((Rcount-x)/2+H-1,H-1)*C((Ccount-y)/2+W-1,W-1)%mod*C(H,x)%mod*C(W,y)%mod);

			}
			return ans;
		}
		int C(int x,int y){ 
			return f[x][y];
		}
		int add(int x,int y){
			x += y;while (x >= mod) x -= mod;
			return x;
		}
};
