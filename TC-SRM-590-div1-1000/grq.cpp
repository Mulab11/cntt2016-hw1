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

const int inf=1e6+7,N=2005,M=500005;
struct node{int to,next,v;};
class max_flow{
	private:
	node p[M];
	int S,T,head[N],st[N],tot;
	queue<int> q;
	bool bfs(int x){
		memset(st,0,sizeof(st));
		st[x]=1;q.push(x);
		while(!q.empty()){
			int x=q.front();q.pop();
			for(int i=head[x];~i;i=p[i].next){
				int y=p[i].to,v=p[i].v;
				if(!v||st[y]) continue;
				st[y]=st[x]+1;q.push(y);
			}
		}
		return st[T]>0;
	}
	int dfs(int x,int f){
		int r=0;
		if(x==T) return f;
		for(int i=head[x];~i;i=p[i].next){
			int y=p[i].to,v=p[i].v,tmp;
			if(!v||st[y]!=st[x]+1) continue;
			tmp=dfs(y,min(f-r,v));
			r+=tmp;
			p[i].v-=tmp;p[i^1].v+=tmp;
			if(r==f)break;
		}
		if(!r) st[x]=-1;
		return r;
	}
	
	public:
	int dinic(){
		int ans=0,t;
		while(bfs(S))
			while(t=dfs(S,inf)) ans+=t;
		return ans;
	}
	void add(int x,int y,int z){
		p[tot].to=y;p[tot].next=head[x];p[tot].v=z;head[x]=tot++;
		p[tot].to=x;p[tot].next=head[y];p[tot].v=0;head[y]=tot++;
	}
	void build(int s,int t){S=s;T=t;}
	void clear(){
		memset(head,-1,sizeof(head));
		tot=0;
	}
}p;

int n,num[44][44];

class FoxAndCity{
public:
	int minimalCost(vector<string> linked, vector<int> want){
		n=linked.size();
		int cnt=0,S=0,T=n*n+1;
		p.clear();p.build(S,T);
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++) num[i][j]=++cnt;
		for(int i=0;i<n;i++){
			for(int j=1;j<n;j++)
				p.add(num[i][j-1],num[i][j],i?sqr(j-want[i]):inf);
			p.add(S,num[i][0],i?inf:0);
			p.add(num[i][n-1],T,inf);
		}
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++){
				if(linked[i][j]=='N') continue;
				for(int k=0;k<n-1;k++)
					p.add(num[i][k+1],num[j][k],inf);
			}
		return p.dinic();
	}
};
