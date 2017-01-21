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
#define pq priority_queue
#define rf random_shuffle
#define np next_permutation
#define lb lower_bound
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

const int N=55,M=1<<16,mod=1e9+7;
struct node{
	int to,next;
}p[N<<2];
int frac[N],rec[N];
int tot,head[N],go[N],n,m;
int si[M],dp[N][M],tmp[M];
bool can[M],vis[N];
map<int,int> trans;
vector<string> s;
vi cnt,g[M];
void add(int x,int y){
//	printf("%d %d\n",x,y);
	p[++tot]={y,head[x]},head[x]=tot;
	p[++tot]={x,head[y]},head[y]=tot;
}
inline void ch(int &x,int y){
	x+=y;if(x>=mod) x-=mod;
}
inline int c(int x,int y){
	if(x<y) return 0;
	return (ll)frac[x]*rec[y]%mod*rec[x-y]%mod;
}
bool pre(int x,int y){
	if(s[x].length()>s[y].length()) return 0;
	for(int i=0;i<s[x].size();i++)
		if(s[x][i]!=s[y][i]) return 0;
	return 1;
}
int exp(int x,int y){
	int ans=1;
	while(y){
		if(y&1) ans=(ll)ans*x%mod;
		x=(ll)x*x%mod;y>>=1;
	}
	return ans;
}
void pre(){
	frac[0]=1;
	for(int i=1;i<=50;i++) frac[i]=(ll)frac[i-1]*i%mod;
	rec[50]=exp(frac[50],mod-2);
	for(int i=49;i>=0;i--) rec[i]=(ll)rec[i+1]*(i+1)%mod;
}
inline void dfs(int x){
	vis[x]=1;
	memset(dp[x],0,sizeof(dp[x]));
	dp[x][0]=1;
	for(int pt=head[x];pt;pt=p[pt].next){
		int y=p[pt].to;
		if(vis[y]) continue;
		dfs(y);
		memcpy(tmp,dp[x],sizeof(tmp));
		for(int i=0;i<(1<<m);i++){
			dp[x][i]=0;
			if(!can[i]) continue;
			for(int j=0;j<g[i].size();j++){
				int k=g[i][j];
				ch(dp[x][i],(ll)dp[y][k]*tmp[i^k]%mod);
			}
		}
	}
	memcpy(tmp,dp[x],sizeof(tmp));
	for(int i=0;i<(1<<m);i++){
		dp[x][i]=0;
		if(!can[i]) continue;
		for(int j=0;j<g[i].size();j++){
			int k=g[i][j];
			if(si[i]-si[k]>cnt[x]) continue;
			ch(dp[x][i],tmp[k]%mod*c(cnt[x],si[i]-si[k])%mod);
		}
	}
//	printf("%d %d %d\n",x,dp[x][2],dp[x][3]);
}

class SimilarNames{
public:
	int count(vector <string> names, vector <int> info1, vector <int> info2){
		//----------------clear------------------
		pre();
		tot=0;memset(head,0,sizeof(head));
		memset(go,0,sizeof(go));
		s.clear();cnt.clear();trans.clear();
		//----------------clear------------------
		
		n=names.size();names.pb("");
		sort(names.begin(),names.end());
		s.pb("");cnt.pb(0);
		for(int i=1;i<=n;i++)
			if(names[i]==names[i-1]) cnt[cnt.size()-1]++; else s.pb(names[i]),cnt.pb(1);
//		return 0;
		n=s.size()-1;
		for(int i=1;i<=n;i++)
			for(int j=i-1;j>=0;j--)
				if(pre(j,i)){add(j,i);break;}
		m=0;
		for(int i=0;i<info1.size();i++){
			if(!trans[info1[i]]) trans[info1[i]]=++m;
			info1[i]=trans[info1[i]]-1;
			if(!trans[info2[i]]) trans[info2[i]]=++m;
			info2[i]=trans[info2[i]]-1;
			go[info1[i]]|=1<<info2[i];
		}
		for(int i=0;i<(1<<m);i++){
			can[i]=1;si[i]=0;
			for(int j=0;j<m;j++)
				if(i&(1<<j)){
					si[i]++;
					if((i&go[j])!=go[j]) can[i]=0;
				}
//			if(can[i]) debug(i);
		}
		for(int i=0;i<(1<<m);i++){
			g[i].clear();
			if(!can[i]) continue;
			for(int j=i;j;j=(j-1)&i)
				if(can[j]) g[i].pb(j);
			g[i].pb(0);
		}
//		debuge;
		memset(vis,0,sizeof(vis));
		dfs(0);
		return (ll)dp[0][(1<<m)-1]*frac[n-m]%mod;
	}
};