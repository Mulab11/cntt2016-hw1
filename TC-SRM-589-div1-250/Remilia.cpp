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
using namespace std;
const int maxn=55;
int fa[maxn],ans,n;
int getfa(int x){return x==fa[x]?x:fa[x]=getfa(fa[x]);}
int cnt[maxn],sum[maxn],mx[maxn];

/*
要对应的字符之间连一条边。
每个连通块的代价是总量减去出现次数最多的。
*/

class GooseTattarrattatDiv1{
public:
	int getmin(string s){
		n=s.size();
		rep(i,0,25) fa[i]=i;
		rep(i,0,n-1) cnt[s[i]-'a']++;
		rep(i,0,(n-1)/2){
			int u=s[i]-'a',v=s[n-i-1]-'a';
			if (getfa(u)!=getfa(v)) fa[fa[u]]=fa[v];
		}
		rep(i,0,25){
			sum[getfa(i)]+=cnt[i];
			mx[getfa(i)]=max(mx[getfa(i)],cnt[i]);
		}
		int ans=0;
		rep(i,0,25) ans+=sum[i]-mx[i];
		return ans;
	}
};
