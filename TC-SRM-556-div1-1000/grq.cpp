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

const string A[2]={"No","Yes"};

const int inf=1e9+7,N=1005,M=500005;
struct node{
	int to,next,v;
};
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

bool solve(vector <string> bridges, int a1, int a2, int an, int b1, int b2, int bn){
	int n=bridges.size();
	p.clear();
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(bridges[i][j]=='N') p.add(i,j,inf);
			else if(bridges[i][j]=='O') p.add(i,j,1);
	p.build(n,n+1);
	p.add(n,a1,an);p.add(a2,n+1,an);
	p.add(n,b1,bn);p.add(b2,n+1,bn);
	return p.dinic()>=an+bn;
}

class OldBridges{
public:
	string isPossible(vector <string> bridges, int a1, int a2, int an, int b1, int b2, int bn){
		bool isok=1;
		return A[solve(bridges,a1,a2,an,b1,b2,bn)&solve(bridges,a1,a2,an,b2,b1,bn)];
	}
};
