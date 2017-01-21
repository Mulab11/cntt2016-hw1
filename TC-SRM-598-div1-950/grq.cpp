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


const int N=55;
struct node{
	int to,next;
}p[N<<2];
int head[N],n,tot;
bool vis[N];
void add(int x,int y){
	p[++tot]=(node){y,head[x]};head[x]=tot;
	p[++tot]=(node){x,head[y]};head[y]=tot;	
}

int dfs(int x){
	vis[x]=1;
	int ans=0,tmp=0;
	for(int i=head[x];i;i=p[i].next){
		int y=p[i].to,t;
		if(vis[y]) continue;
		t=dfs(y);
		if(t) ans+=t; else tmp++;
	}
	if(tmp>1) ans+=tmp-1;
	return ans;
}

class TPS{
public:
	int minimalBeacons(vector <string> linked){
		tot=0;memset(head,0,sizeof(head));
		n=linked.size();
		if(n==1) return 0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(linked[i-1][j-1]=='Y') add(i,j);
		int ans=n+1;
		for(int i=1;i<=n;i++){
			memset(vis,0,sizeof(vis));
			ans=min(ans,dfs(i)+1);
		}
		return  ans;
		
	}
};