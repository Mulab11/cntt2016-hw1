#include <bits/stdc++.h>
#define N 200005
#define M 400005

using namespace std;
inline int read(){
	int ret=0;char ch=getchar();
	bool flag=0;
	while (ch<'0'||ch>'9'){
		flag=ch=='-';
		ch=getchar();
	}
	while ('0'<=ch&&ch<='9'){
		ret=ret*10-48+ch;
		ch=getchar();
	}
	return flag?-ret:ret;
}

int sum;
struct edge{
	int adj,next;
	edge(){}
	edge(int _adj,int _next):adj(_adj),next(_next){}
} e[M];
int n,g[N],m;
void AddEdge(int u,int v){
	e[++m]=edge(v,g[u]);g[u]=m;
	e[++m]=edge(u,g[v]);g[v]=m;
}

bool col[N];
int size[N];
int fa[N];
void dfs0(int u){
	for (int i=g[u];i;i=e[i].next){
		int v=e[i].adj;
		if (v==fa[u]) continue;
		fa[v]=u;
		dfs0(v);
		size[u]+=size[v];
	}
}

int dfs(int u){
//	printf("%d %d\n",u,sum);
	printf("%d ",u);
	int ret=0;
	if (!size[u]) return ret;
	for (int i=g[u];i;i=e[i].next){
		int v=e[i].adj;
		if (v==fa[u]) continue;
		while (size[v]){
			ret+=col[v]*2-1;
			size[v]-=col[v]*2-1;
			sum-=col[v]*2-1;
			col[v]^=1;
			
			ret+=dfs(v);
			if (!sum) return ret;
			
			ret+=col[u]*2-1;
			sum-=col[u]*2-1;
			col[u]^=1;
			printf("%d ",u);
//			printf("%d %d\n",u,sum);
		}
		if (!sum) return ret;
	}
	size[u]-=ret;
	return ret;
}


int main(){
//	freopen("input.txt","r",stdin);
//	freopen("output.txt","w",stdout);
	n=read();
	for (int i=1;i<=n;++i) size[i]=col[i]=read()<0;
	memset(g,0,sizeof(g));m=1;
	for (int i=1;i<n;++i) AddEdge(read(),read());
	fa[1]=0;
	dfs0(1);
	sum=size[1];
	dfs(1);
	if (sum){
		int x=e[g[1]].adj;
		printf("%d %d %d",x,1,x);
	}
	puts("");
	return 0;
}
