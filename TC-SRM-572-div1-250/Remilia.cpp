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
const int maxn=55;
vector<int>cal[maxn];
int cnt[26],fa[maxn];
int getfa(int x){return x==fa[x]?x:fa[x]=getfa(fa[x]);}
/*
把要相同的点用并查集缩起来，每个块改成出现次数最多的那种颜色
*/
struct NewArenaPassword{
	int minChange(string s,int K){
		int n=s.size(),ans=n;
		rep(i,0,n-1) fa[i]=i;
		rep(i,0,K-1){
			int u=i,v=n-K+i,fu=getfa(u),fv=getfa(v);
			if (fu!=fv) fa[fv]=fu;
		}
		rep(i,0,n-1) cal[getfa(i)].pb(i);
		rep(i,0,n-1){
			if (!cal[i].size()) continue;
			memset(cnt,0,sizeof cnt);
			rep(j,0,cal[i].size()-1) cnt[s[cal[i][j]]-'a']++;
			int mx=0;
			rep(j,0,25) mx=max(mx,cnt[j]);
			ans-=mx;
		}
		return ans;
	}
};
