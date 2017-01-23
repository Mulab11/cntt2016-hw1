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

const int inf=1e9+7,N=2555,M=500005,u[4][2]={1,0,0,1,-1,0,0,-1};
struct node{int to,next,v;};
class max_flow{
private:
	node p[M];
	int S,T,head[N],st[N],tot;
	queue<int> q;
	bool bfs(int x){
		memset(st,0,sizeof(st));
		while(!q.empty()) q.pop();
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
	void add(int x,int y,int z){
		p[tot].to=y;p[tot].next=head[x];p[tot].v=z;head[x]=tot++;
		p[tot].to=x;p[tot].next=head[y];p[tot].v=0;head[y]=tot++;
	}
	int dinic(){
		int ans=0,t;
		while(bfs(S))
			while(t=dfs(S,inf)) ans+=t;
		return ans;
	}
	void build(int s,int t){S=s;T=t;}
	void clear(){
		memset(head,-1,sizeof(head));
		tot=0;
	}
}p;
int n,num[55][55];

class FoxAndGo3 {
public:
	int maxEmptyCells(vector<string> board) {
		n=board.size();
		int S=0,T=n*n+1,cnt=0,ans=0;
		p.clear();p.build(S,T);
		for(int i=0;i<n;i++) for(int j=0;j<n;j++) num[i][j]=++cnt;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++){
				if(board[i][j]=='x') continue;
				ans++;
				if(board[i][j]=='.'){p.add(num[i][j],T,1);continue;}
				p.add(S,num[i][j],1);
				for(int k=0;k<4;k++){
					int x=i+u[k][0],y=j+u[k][1];
					if(x<0||y<0||x>=n||y>=n||board[x][y]!='.') continue;
					p.add(num[i][j],num[x][y],inf);
				}
			}
		return ans-p.dinic();
	}
};

