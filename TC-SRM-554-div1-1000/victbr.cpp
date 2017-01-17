/*
1111 1112 1121 1122 1123 1211 1212 1213 
1221 1222 1223 1231 1232 1233 1234
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 121,mod = 1234567891;
const int STATE[15][4] ={
	{1,1,1,1},
	{1,1,1,2},
	{1,1,2,1},
	{1,1,2,2},
	{1,1,2,3},
	{1,2,1,1},
	{1,2,1,2},
	{1,2,1,3},
	{1,2,2,1},
	{1,2,2,2},
	{1,2,2,3},
	{1,2,3,1},
	{1,2,3,2},
	{1,2,3,3},
	{1,2,3,4},
};
int add(int x,int y){
	ll u = x;
	u += y;
	while (u >= mod) u -= mod;
	return u;
}
struct Matrix{
	int a[N][N];
};
struct Ans{
	int a[N];
};

Matrix operator * (const Matrix &a,const Matrix &b){
	Matrix c;memset(c.a,0,sizeof(c.a));
	for (int i = 0;i < N;i++)
		for (int j = 0;j < N;j++)
			for (int k = 0;k < N;k++)
				c.a[i][j] = add(c.a[i][j],(ll)a.a[i][k]*b.a[k][j]%mod);
	return c;
}
Ans operator * (const Ans &a,const Matrix &b){
	Ans c;memset(c.a,0,sizeof(c.a));
	for (int i = 0;i < N;i++)
		for (int j = 0;j < N;j++)
			c.a[j] = add(c.a[j],(ll)a.a[i]*b.a[i][j]%mod);
	return c;
}

class TheBrickTowerHardDivOne{	
	public:
		Matrix A;
		Ans F;
		int used[10],name[10];
		int g[6000][10],a[5],KK,CC,b[5];
		int find(int C, int K, long long H){
			init();
			CC = C;KK = K;
			for (int i = 0;i < 15;i++){
				memset(used,0,sizeof(used));
				for (int j = 0;j < 4;j++)
					used[STATE[i][j]]++;
				used[0] = 1;
				dfs(0,i);
			}
			for (int i = 0;i < N;i++) A.a[i][120] = 1;
			
			for (int i = 0;i < 15;i++){
				int hight = 0,cnt = 0;
				for (int j = 0;j < 4;j++) hight = max(hight,STATE[i][j]);
				for (int j = 0;j < 3;j++) if (STATE[i][j] == STATE[i][j+1]) cnt++;
				if (STATE[i][0] == STATE[i][3]) cnt++;
				if (cnt <= K)F.a[cal(i,cnt)] = P(C,hight); 
			}
			while (H){
				if (H&1) F = F * A;
				A = A * A;
				H >>= 1;
			}
			return F.a[120];
		}
		void init(){
			g[0][0] = 1;
			for (int i = 1;i <= 5000;i++){
				g[i][0] = 1;
				for (int j = 1;j <= 8 && i-j+1 > 0;j++)
					g[i][j] = (ll)g[i][j-1]*(i-j+1)%mod;
			}
		}
		void dfs(int p,int x){
			if (p >= 4){				
				int cnt = 0,color1 = 0,color2 = 0,y = 15,len = 0;
				for (int j = 0;j < 4;j++) {
					color1 = max(color1,STATE[x][j]);
					color2 = max(color2,a[j]);
					if (STATE[x][j] == a[j]) cnt++;
				}
				for (int j = 0;j < 3;j++) if (a[j] == a[j+1]) cnt++;
				if (a[0] == a[3]) cnt++;
				memset(name,0,sizeof(name));
				for (int i = 0;i < 4;i++){
					if (name[a[i]] == 0) {
						b[i] = ++len;
						name[a[i]] = len;
					}
					else b[i] = name[a[i]];
				}
				for (int i = 0;i < 15;i++){
					bool flag = 1;
					for (int j = 0;j < 4;j++)
						if (b[j] != STATE[i][j]) flag = 0;
					if (flag) y = i;
				}
				for (int i = 0;i +cnt <= KK;i++){
					int u = cal(x,i),v = cal(y,i+cnt);
					A.a[u][v] = add(A.a[u][v],P(CC-color1,color2-color1));
				}
				return;
			}
			for (int i = 1;i <= 8;i++)
				if (used[i-1]){
					used[i]++;
					a[p] = i;
					dfs(p+1,x);
					used[i]--;
				}
		}
		int cal(int x,int y){
			return x*8+y;
		}
		int P(int x,int y){
			if (x < 0) return 0;
			if (y < 0) return 1;
			return g[x][y];
		}
};

