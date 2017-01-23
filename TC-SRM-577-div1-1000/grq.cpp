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

const int N=55,M=10005;
int S,T,n,m,num[N][N],u[4][2]={1,0,0,1,-1,0,0,-1};
vector<string> a;
bool black(int x,int y){
	if(x<0||y<0||x>=n||y>=m) return 0;
	return a[x][y]=='#';
}

struct node{
	int to,next,flow;
}p[M<<1];
int head[M],st[M],tot;
queue<int> q;
void add(int x,int y,int z){
//	printf("%d %d %d\n",x,y,z);
	p[++tot]=(node){y,head[x],z};head[x]=tot;
	p[++tot]=(node){x,head[y],0};head[y]=tot;
}
bool bfs(){
	memset(st,0,sizeof(st));
	q.push(S);st[S]=1;
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=head[x];i;i=p[i].next){
			if(!p[i].flow) continue;
			int y=p[i].to;
			if(st[y]) continue;
			st[y]=st[x]+1;q.push(y);
		}
	}
//	for(int i=S;i<=T;i++) printf("%d ",st[i]);puts("");
	return st[T];
}
inline int dfs(int x,int f){
//	debug(x);
	if(x==T) return f;
	int res=0;
	for(int i=head[x];i;i=p[i].next){
		if(!p[i].flow) continue;
		int y=p[i].to,tmp;
		if(st[y]!=st[x]+1) continue;
		tmp=dfs(y,min(f-res,p[i].flow));
		res+=tmp;
		p[i].flow-=tmp;p[i^1].flow+=tmp;
		if(res==f) break;
	}
	if(!res) st[x]=-2;
	return res;
}

int dinic(){
	int t,ans=0;
	while(bfs())
		while(t=dfs(S,1e9)) ans+=t;
	return ans;
}

class BoardPainting{
public:
	int minimalSteps(vector <string> target){
		memset(head,0,sizeof(head));
		tot=1;
		a=target;
		n=a.size();m=a[0].size();
		S=0,T=n*m+1;
		int cnt=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				num[i][j]=++cnt;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++){
				if(a[i][j]=='.')  continue;
				for(int k=0;k<4;k++){
					int x=i+u[k][0],y=j+u[k][1];
					if(!black(x,y)){
						if(k&1) add(S,num[i][j],1); else add(num[i][j],T,1);
					}
					else add(num[i][j],num[x][y],1);
				}
			}
		return dinic()/2;
	}
};
