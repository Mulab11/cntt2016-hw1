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
const int maxn=4200,maxy=135;
struct state{
	int g,w;
	state(int G=0,int W=0){g=G,w=W;}
	bool operator <(const state&x)const{return w==x.w?g<x.g:w<x.w;}
}f[maxn][maxy];
int vis[maxn][maxy];
int ans=0,n;

/*
傻逼DP，dp[mask][r]表示用了mask这些点，用了r个红钥匙，最少用几个白钥匙。
由此，因为获得的钥匙总数是确定的，要用掉的也是确定的。可以算出用了几个绿钥匙。也就知道了每种钥匙剩下的数量，就可以转移了。 
*/

class KeyDungeonDiv1{
public:
	int maxKeys(VI dR,VI dG,VI rR,VI rG,VI rW,VI keys){
		n=dR.size();
		rep(i,0,(1<<n)-1) rep(j,0,(n+1)*10) f[i][j]=state(-1,-1);
		f[0][keys[0]]=state(keys[1],keys[2]);
		vis[0][keys[0]]=1;
		rep(i,0,(1<<n)-1) rep(j,0,(n+1)*10){
			if (!vis[i][j]) continue;
			ans=max(ans,j+f[i][j].g+f[i][j].w);
			rep(k,0,n-1){
				if (((i>>k)&1)^1){
					int rr=j,rg=f[i][j].g,rw=f[i][j].w;
					if (rr>=dR[k]) rr-=dR[k];else rw-=dR[k]-rr,rr=0;
					if (rg>=dG[k]) rg-=dG[k];else rw-=dG[k]-rg,rg=0;
					if (rw<0) continue;
					rr+=rR[k],rg+=rG[k],rw+=rW[k];
					f[i|(1<<k)][rr]=max(f[i|(1<<k)][rr],state(rg,rw));
					vis[i|(1<<k)][rr]=1;
				}
			}
		}
		return ans;
	}
};
