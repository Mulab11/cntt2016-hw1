#include <bits/stdc++.h>

using namespace std;

const int inf=0x3f3f3f3f,dx[]={0,-1,0,1},dy[]={1,0,-1,0};
int n,m,s,t,fst[1005],nxt[100005],to[100005],w[100005],tt;
int d[1005],q[1005];
int getv(char c){//字符转换成数字 
	if(isdigit(c))return c-48;
	if(islower(c))return c-87;
	return c-29;
}
int gs(int x,int y){return x*m+y+1;}//坐标转换成下标 
void ad(int x,int y,int z){//加边 
	nxt[++tt]=fst[x];fst[x]=tt;to[tt]=y;w[tt]=z;
	nxt[++tt]=fst[y];fst[y]=tt;to[tt]=x;w[tt]=0;
}
bool bfs(){//建立层次图 
	memset(d,0,sizeof d);
	int l=0,r=0;q[0]=s;d[s]=1;
	while(l<=r){
		int x=q[l++];
		for(int i=fst[x];i;i=nxt[i])
		if(w[i]&&!d[to[i]])
			d[q[++r]=to[i]]=d[x]+1;
	}
	return d[t];
}
int dfs(int x,int a){//增广 
	if(x==t||a==0)return a;
	int ret=0,f;
	for(int i=fst[x];i;i=nxt[i])
	if(d[to[i]]==d[x]+1&&(f=dfs(to[i],min(a,w[i])))){
		ret+=f; a-=f;
		w[i]-=f; w[i^1]+=f;
		if(a==0)break;
	}
	return ret;
}

class SurroundingGame {
public:
	int maxScore(vector <string> cost, vector <string> benefit) {
		n=cost.size(); m=cost[0].size();
		int ans=0;
		for(int i=0;i<n;++i)
			for(int j=0;j<m;++j)ans+=getv(benefit[i][j]);//先加上收益 
		s=n*m*2+1; t=n*m*2+2; tt=1;
		for(int i=0;i<n;++i)
			for(int j=0;j<m;++j){//最小割建图 
				int x=gs(i,j);
				if((i+j)%2){
					ad(s,x,getv(cost[i][j]));
					ad(x,x+n*m,getv(benefit[i][j]));
					for(int k=0,xx,yy;k<4;++k){
						xx=i+dx[k],yy=j+dy[k];
						if(0<=xx&&xx<n&&0<=yy&&yy<m)
							ad(x+n*m,gs(xx,yy),inf);
					}
				}else{
					ad(x,t,getv(cost[i][j]));
					ad(x+n*m,x,getv(benefit[i][j]));
					for(int k=0,xx,yy;k<4;++k){
						xx=i+dx[k],yy=j+dy[k];
						if(0<=xx&&xx<n&&0<=yy&&yy<m)
							ad(gs(xx,yy),x+n*m,inf);
						}
				}
			}
		while(bfs())ans-=dfs(s,inf);//dinic 
		return ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
