#include <bits/stdc++.h>

#define rep(x,a,b) for (int x=a;x<=(int)b;x++)
#define drp(x,a,b) for (int x=a;x>=(int)b;x--)
#define cross(x,a) for (int x=hd[a];~x;x=nx[x])
#define ll long long
#define inf (1<<29)
#define PII pair<int,int>
#define PDD pair<double,double>
#define mk(a,b) make_pair(a,b)
#define fs first
#define sc second
#define pb push_back
using namespace std;
const int maxn=2505,maxm=200005;
int n,m;
int id(int x,int y){
	return x*m+y+1;
}
int to[maxm],nx[maxm],cap[maxm],hd[maxn],cnt;
void addedge(int u,int v,int cp){
	to[cnt]=v;nx[cnt]=hd[u];cap[cnt]=cp;hd[u]=cnt++;
	to[cnt]=u;nx[cnt]=hd[v];cap[cnt]=0;hd[v]=cnt++;
}
int dep[maxn],S,T,head,tail,que[maxn];
bool bfs(){
	memset(dep,-1,sizeof dep);
	dep[S]=0;
	head=1,tail=0;
	que[++tail]=S;
	while (head<=tail){
		int u=que[head++];
		cross(i,u){
			int v=to[i];
			if (cap[i]&&dep[v]==-1){
				dep[v]=dep[u]+1;
				if (v==T) return 1;
				que[++tail]=v;
			}
		}
	}
	return 0;
}
int dfs(int u,int f){
	if (u==T||!f) return f;
	int ret=0,tmp;
	cross(i,u){
		int v=to[i];
		if (dep[v]==dep[u]+1&&(tmp=dfs(v,min(f,cap[i])))!=0){
			cap[i]-=tmp,cap[i^1]+=tmp;
			ret+=tmp,f-=tmp;
			if (!f) break;
		}
	}
	if (!ret) dep[u]=-1;
	return ret;
}
int flow(){
	int ret=0;
	while (bfs()) ret+=dfs(S,inf);
	return ret;
}

/*
最大权闭合子图的沙包建图
*/

class FoxAndGo3{
public:
	int maxEmptyCells(vector<string>a){
		n=a.size(),m=a[0].size();
		int ans=0;
		S=0,T=n*m+1;
		memset(hd,-1,sizeof hd);cnt=0;
		rep(i,0,n-1) rep(j,0,m-1){
			if (a[i][j]=='o'){
				int nd=id(i,j);
				addedge(S,nd,1);ans++;
				if (i>0&&a[i-1][j]=='.') addedge(nd,id(i-1,j),inf);
				if (j>0&&a[i][j-1]=='.') addedge(nd,id(i,j-1),inf);
				if (i<n-1&&a[i+1][j]=='.') addedge(nd,id(i+1,j),inf);
				if (j<m-1&&a[i][j+1]=='.') addedge(nd,id(i,j+1),inf); 
			}
			if (a[i][j]=='.'){
				ans++;
				addedge(id(i,j),T,1);
			}
		}
		return ans-flow();
	}
};
