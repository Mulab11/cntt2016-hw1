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

const int inf=1e9+7,N=1005,M=500005;
int u[4][2]={0,1,1,0,0,-1,-1,0};
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
	int dinic(){
		int ans=0,t;
		while(bfs(S))
			while(t=dfs(S,inf)) ans+=t;
		debug(ans);
		return ans;
	}
	void build(int s,int t){S=s;T=t;}
	void clear(){
		memset(head,-1,sizeof(head));
		tot=0;
	}
	void add(int x,int y,int z){
		if(!z) return;
//		printf("%d %d %d\n",x,y,z);
		p[tot].to=y;p[tot].next=head[x];p[tot].v=z;head[x]=tot++;
		p[tot].to=x;p[tot].next=head[y];p[tot].v=0;head[y]=tot++;
	}
}sol;
int n,m,tot,b[25][25],c[25][25],num[25][25],num2[25][25];

int get(char x){
	if(x>='0'&&x<='9') return x-'0';
	if(x>='a'&&x<='z') return x-'a'+10;
	return x-'A'+36;
}

class SurroundingGame{
public:
	int maxScore(vector <string> cost, vector <string> benefit){
		n=cost.size();m=cost[0].size();
		sol.clear();tot=0;
		int S=0,T=n*m*2+1,ans=0;
		sol.build(S,T);
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++){
				int b=get(benefit[i][j]),c=get(cost[i][j]);
				ans+=b;
				num[i][j]=++tot;num2[i][j]=++tot;
				if((i&1)^(j&1)) 
					sol.add(num[i][j],num2[i][j],b),sol.add(S,num[i][j],c);
				else
					sol.add(num2[i][j],num[i][j],b),sol.add(num[i][j],T,c);
			}
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				for(int k=0;k<4;k++){
					int x=i+u[k][0],y=j+u[k][1];
					if(x<0||y<0||x>=n||y>=m) continue;
					if((i&1)^(j&1)) sol.add(num[i][j],num2[x][y],inf);
					else sol.add(num2[x][y],num[i][j],inf);
				}
		return ans-sol.dinic();
	}
};
