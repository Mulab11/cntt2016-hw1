#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 2500+10;

class LittleElephantAndRGB{
	public:
		int g[N][N],f[N][2],h[N];
		ll ans;
		int n,m;
		string s;
		long long getNumber(vector <string> list, int minGreen){
			s = ' ';m = minGreen;
			for (int i = 0;i < list.size();i++)
				s = s + list[i];
			n = s.size()-1;

			int now = 0;
			for (int i = n;i > max(0,n-m+1);i--){//!!!!
				if (s[i] == 'G') now++;else now = 0;
				f[i][0] = f[i+1][0]+1;
			}
//			f[n+1][0] = 1;
			for (int i = n-m+1;i >= 1;i--){
				f[i][1] = f[i+1][1];
				f[i][0] = f[i+1][0]+1;
			
				if (s[i] == 'G') now++;else now = 0;
				if (now == m) {
					f[i][1] += f[i+m][0];
					f[i][0] -= f[i+m][0];  
				}
				if (now >= m) {f[i][1]++;f[i][0]--;}	
			}
			
//			g[0][0] = 1;
			for (int i = 1;i <= n;i++){
				if (s[i] == 'G'){
					for (int j = i;j >= 0;j--)
						if (j < m){
							h[j+1] += h[j];
							h[j] = 0;
						}
					h[1]++;
					h[0] = 0;
				}
				else{
					for (int j = 1;j <= i;j++)
						if (j < m){
							h[0] += h[j];
							h[j] = 0;
						}
					h[0]++;
				}
				for (int j = 0;j <= m;j++)
					g[i][j] = g[i-1][j]+h[j];
			}	
//			for (int i = 1;i <= n;i++) printf("%lld ",f[i][1]);printf("\n");
			/*
			for (int i = 1;i <= n;i++){
				for (int j = 0;j <= m;j++)
					printf("%lld ",g[i][j]);
				printf("\n");
			}*/
			/*
			for (int i = 1;i <= n;i++){
				for (int j = 0;j <= m;j++)
					printf("%d ",g[i][j]);
				printf("AA\n");
			}*/
			
			for (int i = 2;i <= n;i++){
				ans += (ll)g[i-1][m]*(n-i+1);
				int cnt =0,u = i;
				while (s[u] == 'G' && u <= n){
					cnt++;
					ans += (ll)g[i-1][m-cnt]*(n-u+1);
					u++;
					if (cnt+1 >= m) break;
				}
				for (int j = 0;j < m-cnt;j++)
					ans += (ll)g[i-1][j]*f[i][1];
//				ans -= (ll)g[i-1][m]*f[i][1];
//				printf("%d %lld %d\n",i,ans,f[i][1]);
			}
			return ans;
		}
}A;

