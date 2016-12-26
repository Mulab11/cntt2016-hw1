#include <bits/stdc++.h>

#define rep(x,a,b) for (int x=a;x<=(int)b;x++)
#define drp(x,a,b) for (int x=a;x>=(int)b;x--)
#define cross(x,a) for (int x=hd[a];~x;x=nx[x])
#define ll long long
#define inf (1<<29)
#define PII pair<int,int>
#define PDD pair<double,double>
#define mk(a,b) make_pair(a,b)
#define fs first
#define sc second
#define pb push_back
#define VI vector<int>
using namespace std;
const int maxn=55;
vector<int>cal[maxn];
int need[maxn],dsr[maxn],m,n;
ll f[2][maxn][maxn][maxn];
ll C[maxn][maxn];

/*
simple 背包，划分成两个集合。
枚举深度，然后不成功的那一部分的答案可以组合数算。
成功的那一部分的答案可以容斥+退背包或者直接OGF乘除二项式。
最后u=1+x展开的时候系数也是个卷积，反正全部都可以O(n^2)计算。
*/

class Excavations{
public:
	ll count(vector<int>kind,vector<int>dep,vector<int>found,int sel){
		C[0][0]=1;
		rep(i,1,50){
			C[i][0]=1;
			rep(j,1,i) C[i][j]=C[i-1][j-1]+C[i-1][j];
		}
		n=kind.size();
		rep(i,0,n-1) dsr[i]=dep[i];
		sort(dsr,dsr+n);
		m=unique(dsr,dsr+n)-dsr;
		rep(i,0,n-1) cal[kind[i]].pb(lower_bound(dsr,dsr+m,dep[i])-dsr+1);
		rep(i,1,50) sort(cal[i].begin(),cal[i].end());
		rep(i,0,found.size()-1) need[found[i]]=1;
		int fr=0,to=1;
		f[fr][0][0][m+1]=1;
		rep(i,1,50){
			if (!cal[i].size()) continue;
			memset(f[to],0,sizeof f[to]);
			if (need[i]){
				rep(j,0,sel-1) rep(k,0,m) rep(l,k+1,m+1){
					if (!f[fr][j][k][l]) continue;
					for (int _=0;_<cal[i].size()&&cal[i][_]<l;_++) rep(__,0,min(sel-j-1,(int)cal[i].size()-_-1))
						f[to][j+__+1][max(k,cal[i][_])][l]+=f[fr][j][k][l]*C[cal[i].size()-_-1][__];
				}
			}
			else{
				rep(j,0,sel) rep(k,0,m) rep(l,k+1,m+1){
					if (!f[fr][j][k][l]) continue;
					f[to][j][k][l]+=f[fr][j][k][l];
					if (j==sel) continue;
					for (int _=cal[i].size()-1;_>=0&&cal[i][_]>k;_--) rep(__,0,min(sel-j-1,(int)cal[i].size()-_-1))
						f[to][j+__+1][k][min(l,cal[i][_])]+=f[fr][j][k][l]*C[cal[i].size()-_-1][__];
				}	
			}
			fr^=1,to^=1;
		}
		ll ans=0;
		rep(k,0,m) rep(l,k+1,m+1) ans+=f[fr][sel][k][l];
		return ans;
	}
};
