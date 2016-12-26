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
ll f[2][maxn*2];
void upd(ll &x,ll y){
	if (y>x) x=y;
}

/*
f[i]表示用i的价格，如果可行，最多受到多少积累
simple DP
*/

struct MonstersValley{
	int minimumPrice(vector<ll>drd,vector<int>prc){
		int n=drd.size();
		memset(f,-1,sizeof f);
		int fr=0,to=1;
		f[fr][0]=0;
		rep(i,1,n){
			memset(f[to],-1,sizeof f[to]);
			rep(j,0,(i-1)*2){
				if (f[fr][j]==-1) continue;
				if (f[fr][j]>=drd[i-1]) upd(f[to][j],f[fr][j]);
				upd(f[to][j+prc[i-1]],f[fr][j]+drd[i-1]);
			}
			to^=1,fr^=1;
		}
		rep(j,0,n*2) if (~f[fr][j]) return j;
		return -1;
	}
};
