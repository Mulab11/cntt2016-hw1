#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

const int N=55;
struct node{int kind,depth;}p[N];
bool vis[N],use[N];
ll n,ans,c[N][N],dp[2][N];
vector<node> a;

inline bool cmp(node a,node b){
	if(a.depth!=b.depth) return a.depth<b.depth;
	return a.kind<b.kind;
}
inline bool cmp2(node a,node b){return a.kind<b.kind;}
ll solve(int n){
	int k=0;memset(dp[k],0,sizeof(dp[k]));
	dp[k][0]=1;
	for(int i=0;i<a.size();i++){
		k^=1;memset(dp[k],0,sizeof(dp[k]));
		int r=i,cnt;
		while(r+1<a.size()&&a[r+1].kind==a[i].kind) r++;
		cnt=r-i+1;
		for(int j=0;j<=n;j++)
			for(int t=0;t<j;t++)
				if(j-t<=cnt) dp[k][j]+=dp[k^1][t]*c[cnt][j-t];
		i=r;
	}
	return dp[k][n];
}

class Excavations{
public:
	long long count(vector<int> kind, vector<int> depth, vector<int> found, int K){
		n=kind.size();ans=0;
		for(int i=0;i<=n;i++){
			c[i][i]=c[i][0]=1;
			for(int j=1;j<i;j++) c[i][j]=c[i-1][j]+c[i-1][j-1];
		}
		memset(vis,0,sizeof(vis));
		for(int i=0;i<found.size();i++) vis[found[i]]=1;
		for(int i=0;i<n;i++) p[i]=(node){kind[i],depth[i]};
		sort(p,p+n,cmp);
		for(int i=0;i<n;i++){
			if(!vis[p[i].kind]) continue;
			int isok=1,m=0,cnt=0;
			a.clear();memset(use,0,sizeof(use));
			use[p[i].kind]=1;
			for(int j=0;j<i;j++)
				if(vis[p[j].kind]&&p[j].kind!=p[i].kind) a.pb(p[j]),use[p[j].kind]=1,cnt++;
			for(int j=i+1;j<n;j++)
				if(p[j].depth>p[i].depth||(p[j].depth==p[i].depth&&vis[p[j].kind])) {m++;continue;}
			for(int j=1;j<51;j++) if(use[j]!=vis[j]){isok=0;break;}
			if(!isok) continue;
			sort(a.begin(),a.end(),cmp2);
			for(int l=0;l<K&&l<=cnt;l++) ans+=(ll)c[m][K-l-1]*solve(l);
//			printf("%d %d\n",i,(int)a.size());
		}
		return ans;
	}
};
