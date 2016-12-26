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
const int maxn=55,maxm=100005;
string col;
vector<string>mp;
int to[maxm],nx[maxm],cap[maxm],hd[maxn],cnt;
void addedge(int u,int v,int cp){
	to[cnt]=v;nx[cnt]=hd[u];cap[cnt]=cp;hd[u]=cnt++;
	to[cnt]=u;nx[cnt]=hd[v];cap[cnt]=0;hd[v]=cnt++;
}
int que[maxn],head,tail,dep[maxn],n,S,T;
bool bfs(){
	memset(dep,-1,sizeof dep);
	dep[S]=0;
	head=1,tail=0;que[++tail]=S;
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
int dfs(int u,int flow){
	if (u==T||!flow) return flow;
	int ret=0,f;
	cross(i,u){
		int v=to[i];
		if (dep[v]==dep[u]+1&&(f=dfs(v,min(flow,cap[i])))){
			cap[i]-=f,cap[i^1]+=f;
			flow-=f,ret+=f;
			if (!flow) break;
		}
	}
	if (!ret) dep[u]=-1;
	return ret;
}
int maxflow(){
	int ret=0,f;
	while (bfs()){
		while ((f=dfs(S,inf))) ret+=f;
	}
	return ret;
}
int work(char a,char b){
	memset(hd,-1,sizeof hd);cnt=0;
	rep(i,0,n-1){
		if (col[i]==a){
			addedge(S,i+1,1);
			rep(j,0,n-1) if (mp[i][j]=='Y'&&col[j]==b) addedge(i+1,j+1,1);
		}
		if (col[i]==b) addedge(i+1,T,1);
	}
	return maxflow();
}

/*
充要条件是存在某两种颜色之间没有边。
枚举是哪两种颜色，然后是一个二分图最小点覆盖问题。
*/

class GearsDiv1{
public:
	int getmin(string col,vector<string>mp){
		n=col.size();S=0,T=n+1;
		::col=col,::mp=mp;
		return min(min(work('R','G'),work('R','B')),work('G','B'));
	}
};
