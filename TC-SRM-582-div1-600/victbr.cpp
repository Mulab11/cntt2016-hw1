#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1300,M = 65536,mod = 1e9+9;

class ColorfulBuilding{
	public:
		int a[N],pre[N],col[M+10];
		int n,f[2][N],g[N][N];
		int finv[N],inv[N],fact[N];
		string s1,s2;
		int count(vector <string> color1, vector <string> color2, int L){
			init(1296);
			for (int i = 0;i < color1.size();i++)
				s1 = s1 + color1[i];
			for (int i = 0;i < color2.size();i++)
				s2 = s2 + color2[i];
			for (int i = 0;i < s1.size();i++)
				a[i+1] = s1[i]*256+s2[i];
			n = s1.size();
			for (int i = 1;i <= n;i++){
				pre[i] = col[a[i]];
				col[a[i]] = i;
			}
			
			f[0][0] = fact[n-1];
			for (int i = 1;i <= n;i++){
				for (int j = 0;j <= L;j++) f[1][j] = 0;
				f[1][0] = fact[n-1];
				for (int j = 1;j <= L;j++){
					add(f[1][j],f[0][j-1]);
					add(f[1][j],g[pre[i]][j]);
					add(f[1][j],mod-g[pre[i]][j-1]);
					f[1][j] = (ll)f[1][j]*finv[n-i]%mod;
					if (i == n && j == L) return f[1][L];
					if (i < n) f[1][j] = (ll)f[1][j]*fact[n-i-1]%mod;
					add(g[i][j],g[pre[i]][j]);
					add(g[i][j],f[1][j]);
					add(f[1][j],f[0][j]);
				}
				swap(f[0],f[1]);
			}
			return f[1][L];
		}
		void add(int &x,int y){
			x += y;
			while (x >= mod) x -= mod;
		}
		void init(int p){
			fact[0] = 1;
			for (int i = 1;i <= p;i++) 
				fact[i] = (ll)fact[i-1]*i%mod;
			inv[1] = 1;
			for (int i = 2;i <= p;i++) 
				inv[i] = mod-(ll)mod/i*inv[mod%i]%mod;
			finv[0] = 1;
			for (int i = 1;i <= p;i++)
				finv[i] = (ll)finv[i-1]*inv[i]%mod;
		}
}A;

