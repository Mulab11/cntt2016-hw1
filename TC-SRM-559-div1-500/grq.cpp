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
struct node{
	int to,next;
}p[N<<2];
int n,tot,head[N],du[N],dp[N],hei[N];
bool vis[N];
inline void add(int x,int y){
	p[++tot]=(node){y,head[x]};head[x]=tot;
	p[++tot]=(node){x,head[y]};head[y]=tot;
	du[x]++;du[y]++;
}
void dfs(int x){
	vis[x]=1;dp[x]=hei[x]=0;
	int si=0,l=0,r=0;
	for(int i=head[x];i;i=p[i].next){
		int y=p[i].to;
		if(vis[y]) continue;
		dfs(y);si++;
		if(si==1) l=y; else if(si==2) r=y;
	}
	if(si>2) return;
	if(hei[l]<hei[r]) swap(l,r);
	if(!si){dp[x]=1;hei[x]=1;return;}
	if(si==1){
		if(dp[l]==1&&hei[l]==1) dp[x]=2,hei[x]=2;
		return ;
	}
	if(dp[l]==1&&dp[r]==1&&hei[l]==hei[r]) dp[x]=1;
	else if(dp[l]==1&&dp[r]==1&&hei[l]==hei[r]+1) dp[x]=2;
	else if(dp[l]==2&&dp[r]==1&&hei[l]<=hei[r]+1) dp[x]=2;
	else if(dp[l]==1&&dp[r]==2&&hei[r]==hei[l]) dp[x]=2;
	hei[x]=hei[l]+1;
}

class HatRack{
public:
	long long countWays(vector <int> knob1, vector <int> knob2){
		n=knob1.size()+1;
		if(n==2) return 2;
		tot=0;
		memset(head,0,sizeof(head));
		memset(du,0,sizeof(du));
		for(int i=0;i<n-1;i++) add(knob1[i],knob2[i]);
		int sum=0;ll ans=0;
		for(int i=1;i<=n;i++)
			if(du[i]==2){
				sum++;if(sum>2) return 0;
				memset(vis,0,sizeof(vis));dfs(i);
				printf("root=%d\n",i);
				for(int j=1;j<=n;j++) printf("%d %d\n",dp[j],hei[j]);
				if(dp[i]){
					ll tmp=1;
					for(int j=1;j<=n;j++)
						if(dp[j]==1&&hei[j]!=1) tmp=tmp*2;
					ans+=tmp;
				}
			}
		return ans;
	}
};
