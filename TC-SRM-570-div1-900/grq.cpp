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

const int maxn=30,N=3005,mod=N-5,M=320005,inf=1e9;

struct node{
	int to,next,flow,cost;
}p[M];
int head[N],tot,k,q[N],S,T,from[N],use[N],d[N];
int n,m,num[maxn][maxn],a[maxn][maxn],b[maxn][maxn];
bool vis[N];
inline void add(int x,int y,int f,int w){
	p[tot]=(node){y,head[x],f,w};head[x]=tot++;
	p[tot]=(node){x,head[y],0,-w};head[y]=tot++;
}
inline int inc(int &x){x++;if(x>=mod) x-=mod;return x;}
inline bool spfa(){
	int h=0,t=1;
	memset(vis,0,sizeof(vis));
	for(int i=S;i<=T;i++) d[i]=inf;
	vis[S]=1;q[t]=S;d[S]=0;
	while(h!=t){
		int x=q[inc(h)];vis[x]=0;
		for(int i=head[x];~i;i=p[i].next){
			if(!p[i].flow) continue;
			int y=p[i].to,w=p[i].cost;
			if(d[y]>d[x]+w){
				d[y]=d[x]+w;from[y]=x;use[y]=i;
				if(!vis[y]) q[inc(t)]=y,vis[y]=1;
			}
		}
	}
	return d[T]<inf;
}
inline int extend(){
	int x=T,ans=0;
	while(x!=S){
		p[use[x]].flow--;p[use[x]^1].flow++;
		ans+=p[use[x]].cost;
		x=from[x];
	}
	return ans;
}
inline bool check(vector<string> a,int x,int y){
	if(x<0||y<0||x>=n||y>=m) return 0;
	return a[x][y]!='w';
}

class CurvyonRails{
public:
	int getmin(vector<string> field){
		memset(head,-1,sizeof(head));tot=0;
		n=field.size();m=field[0].size();
		S=0;T=n*m*3+2;
		int cnt=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++){
				if(field[i][j]=='w') continue;
				num[i][j]=++cnt;a[i][j]=++cnt;b[i][j]=++cnt;
				if((i+j)&1){
					add(num[i][j],T,2,0);
					add(a[i][j],num[i][j],1,0);	add(a[i][j],num[i][j],1,field[i][j]=='C');
					add(b[i][j],num[i][j],1,0);	add(b[i][j],num[i][j],1,field[i][j]=='C');
				}
				else{
					add(S,num[i][j],2,0);
					add(num[i][j],a[i][j],1,0);	add(num[i][j],a[i][j],1,field[i][j]=='C');
					add(num[i][j],b[i][j],1,0);	add(num[i][j],b[i][j],1,field[i][j]=='C');
				}
			}
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++){
				if(field[i][j]=='w'||((i+j)&1))continue;
				if(check(field,i-1,j)) add(a[i][j],a[i-1][j],1,0);
				if(check(field,i+1,j)) add(a[i][j],a[i+1][j],1,0);
				if(check(field,i,j-1)) add(b[i][j],b[i][j-1],1,0);
				if(check(field,i,j+1)) add(b[i][j],b[i][j+1],1,0);
			}
		
		int ans=0,cap=0;
		while(spfa()) ans+=extend(),cap++;
		if(cap<cnt/3) return -1;
		return ans;
	}
};
