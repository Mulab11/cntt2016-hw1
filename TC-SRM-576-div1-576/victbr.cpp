#include <bits/stdc++.h>

using namespace std;

const int N = 310,mod = 1e9+9;

class TheExperiment{
	public:	
		string s;
		int ans,n,f[N][N][3],a[N],pre[N],A,B;//0 ¿Õ 1 Î´Âú 2 Âú 
		int countPlacements(vector <string> intensity, int M, int L, int AA, int BB){
			n = intensity.size();
			A = AA;B = BB;
			for (int i = 0;i < n;i++) s += intensity[i];
			n = s.size();
			for (int i = 1;i <= n;i++) a[i] = s[i-1]-'0';
			for (int i = 1;i <= n;i++) pre[i] = pre[i-1]+a[i];
			
			f[0][0][0] = 1;
			
			for (int i = 1;i <= n;i++){
				f[i][0][0] = 1;
				for (int j = 1;j <= M;j++){
					add(f[i][j][0],f[i-1][j][0]);
					add(f[i][j][0],f[i-1][j][2]);
					for (int k = max(0,i-L+1);k < i;k++)
						if (check(pre[i]-pre[k])){
							add(f[i][j][1],f[k][j-1][0]);
							add(f[i][j][1],f[k][j-1][1]);
							add(f[i][j][2],f[k][j-1][2]);
						}
					if (L <= i){
						if (check(pre[i]-pre[i-L])) {
							add(f[i][j][2],f[i-L][j-1][0]);
							add(f[i][j][2],f[i-L][j-1][1]);
							add(f[i][j][2],f[i-L][j-1][2]);
						}
					}
				}
			}
			
			add(ans,f[n][M][0]);
			add(ans,f[n][M][2]);
			return ans;
		}
		bool check(int x){
			return A <= x && x <= B;
		}
		void add(int &x,int y){
			x += y;
			while (x >= mod) x -= mod;
		}
};
