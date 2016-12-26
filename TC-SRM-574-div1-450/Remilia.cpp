#include<bits/stdc++.h>

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
const int maxn=20,maxs=270000;
ll f[maxn][maxs];
int N,m;
int pre(int x){return x==1?N:x-1;}
int nxt(int x){return x==N?1:x+1;}
bool neib(int x,int y){
	return x==pre(y)||y==pre(x);
}

/*
连线只要满足分出的两半内都有点即可。
状压Dp
*/

struct PolygonTraversal{
	ll count(int N,vector<int>poi){
		::N=N;
		m=poi.size();
		int y=0;
		rep(i,0,m-1) y|=(1<<poi[i]-1);
		f[poi[m-1]][y]=1;
		ll ans=0;
		rep(i,y,(1<<N)-1) rep(j,1,N){
			if (!f[j][i]) continue;
			if (i==(1<<N)-1){
				if (!neib(j,poi[0])) ans+=f[j][i];
			}
			else{
				int p=pre(j),s=nxt(j);
				while (p!=s&&((i>>p-1)&1)==0) p=pre(p);
				while (s!=p&&((i>>s-1)&1)==0) s=nxt(s);
				if (p==s) continue;
				p=pre(p);
				while (p!=s){
					if (!((i>>p-1)&1)) f[p][i|(1<<p-1)]+=f[j][i];
					p=pre(p);
				}
			}
		}
		return ans;
	}
};
