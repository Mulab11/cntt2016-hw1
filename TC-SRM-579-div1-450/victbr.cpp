#include <bits/stdc++.h>

using namespace std;

const int N = 60,M = 65536+10,inf = 0x3f3f3f3f;

class TravellingPurchasingMan{
	public:
		string s;
		int l[N],r[N],t[N],len,x[N],y[N],z[N],siz;
		int a[N][N],n,f[M][N],ans;
		int maxStores(int N, vector <string> interestingStores, vector <string> roads){
			init(N,interestingStores,roads);
			
			memset(a,0x3f,sizeof(a));
			for (int i = 0;i < n;i++) a[i][i] = 0;
			for (int i = 1;i <= len;i++)
				a[x[i]][y[i]] = a[y[i]][x[i]] = z[i];
			for (int k = 0;k < n;k++)	
				for (int i = 0;i < n;i++)
					for (int j = 0;j < n;j++)
						a[i][j] = min(a[i][j],a[i][k]+a[k][j]);
			memset(f,0x3f,sizeof(f));
			
			
			for (int i = 0;i < siz;i++)
				if (a[n-1][i] <= r[i]) f[(1<<i)][i] = max(l[i],a[n-1][i])+t[i];	

			for (int i = 1;i < (1<<siz);i++){
				for (int j = 0;j < siz;j++)
					if (f[i][j] != inf){
						for (int k = 0;k < siz;k++){
							if (((1<<k)&i) == 0) {
								int u = f[i][j]+a[j][k];
								if (u <= r[k]) 
									f[(1<<k)|i][k] = min(f[(1<<k)|i][k],max(f[i][j]+a[j][k],l[k])+t[k]);
							}
						}
					}
			}
			
			for (int i = 1;i < (1<<siz);i++){
				for (int j = 0;j < siz;j++)
					if (f[i][j] != inf){
						int tot = 0,x = i;
						while (x){
							tot++;
							x -= x &(-x);
						}
						ans = max(ans,tot);
						break;
					}
			}
			return ans;
		}
		void init(int N, vector <string> interestingStores, vector <string> roads){
			n = N;
			s = "";
			for (int i = 0;i < interestingStores.size();i++)
				s = s + interestingStores[i]+" ";
			int val = 0,flag = 0;
			for (int i = 0;i < s.size();i++){
				if ('0' <= s[i] && s[i] <= '9') val = val * 10 + s[i] - '0';
				else{
					if (flag == 0) l[++len - 1] = val;
					else if (flag == 1) r[len - 1] = val;
					else t[len - 1] = val;
					flag = (flag+1)%3;
					val = 0;
				}
			}
			
			s = "";
			for (int i = 0;i < roads.size();i++)
				s = s + roads[i]+" ";
			val = 0;flag = 0;
			for (int i = 0;i < s.size();i++){
				if ('0' <= s[i] && s[i] <= '9') val = val * 10 + s[i] - '0';
				else{
					if (flag == 0) x[++siz] = val;
					else if (flag == 1) y[siz] = val;
					else z[siz] = val;
					flag = (flag+1)%3;
					val = 0;
				}
			}
			swap(siz,len);
		}
};