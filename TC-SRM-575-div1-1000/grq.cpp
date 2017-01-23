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

const int inf=1e9+7,N=5005,M=500005;
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
const int u[4][2]={1,0,0,1,-1,0,0,-1};
int n,m,cnt,in[55][55],out[55][55];

class TheTilesDivOne{
public:
	int find(vector<string> board){
		n=board.size();m=board[0].size();
		p.clear();cnt=0;
		int S=0,T;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				in[i][j]=++cnt,out[i][j]=++cnt,p.add(in[i][j],out[i][j],1);
		T=cnt+1;
		p.build(S,T);
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++){
				if(board[i][j]=='X') continue;
				if((i+j)%2==0){
					for(int k=0;k<4;k++){
						int x=i+u[k][0],y=j+u[k][1];
						if(x<0||y<0||x>=n||y>=m||board[x][y]=='X') continue;
						if(x&1) p.add(out[x][y],in[i][j],1); else p.add(out[i][j],in[x][y],1);
					}
				}
				else if(i&1) p.add(S,in[i][j],1); else p.add(out[i][j],T,1);
			}
		return p.dinic();
	}
};
