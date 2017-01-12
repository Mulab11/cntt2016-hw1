#include <bits/stdc++.h>

using namespace std;

int n,fst[555],to[555],nxt[555],fa[555],f[555],tt,li[555];
void ad(int x,int y){//加边 
	nxt[++tt]=fst[x];fst[x]=tt;to[tt]=y;fa[y]=x;
}
void dfs(int x,int v){//搜索所有后继状态 
	for(int i=fst[x];i;i=nxt[i])v^=f[to[i]];
	li[++tt]=v;
	for(int i=fst[x];i;i=nxt[i])dfs(to[i],v^f[to[i]]);
}
int dfs(int x){//树形dp 
	for(int i=fst[x];i;i=nxt[i])dfs(to[i]);
	tt=0;
	dfs(x,0);
	sort(li+1,li+tt+1);
	tt=unique(li+1,li+tt+1)-li-1;
	if(li[1]!=0)f[x]=0;
	else {
		for(int i=1;i<=tt;++i){//计算mex 
			f[x]=li[i]+1;
			if(i<tt&&li[i+1]!=f[x])break;
		}
	}
	return f[x];
}

class CirclesGame {
public:
	string whoCanWin(vector <int> x, vector <int> y, vector <int> r) {
		n=x.size();
		for(int i=0;i<n;++i){
			int p=-1,v=99999;
			for(int j=0;j<n;++j)
			if(r[i]<r[j]&&r[j]<v&&(r[i]-r[j])*(r[i]-r[j])>(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))p=j,v=r[j];
			if(p!=-1)ad(p+1,i+1);//建图 
		}
		int ans=0;
		for(int i=1;i<=n;++i)if(!fa[i])ans^=dfs(i);//sg 
		if(ans)return "Alice";else return "Bob";
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
