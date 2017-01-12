#include <bits/stdc++.h>

using namespace std;

const int inf=0x3f3f3f3f;
int g[55][55],n,s,t,q[55],d[55];
bool bfs(){//bfs建立层次图 
	memset(d,0,sizeof d);
	int l=0,r=0;q[0]=s;d[s]=1;
	while(l<=r){
		int x=q[l++];
		for(int i=0;i<=t;++i)
		if(g[x][i]&&!d[i])
			d[q[++r]=i]=d[x]+1;
	}
	return d[t];
}
int dfs(int x,int a){//增广 
	if(x==t||a==0)return a;
	int ret=0,tmp;
	for(int i=0;i<=t;++i)
	if(d[i]==d[x]+1&&(tmp=dfs(i,min(a,g[x][i])))){
		g[x][i]-=tmp;g[i][x]+=tmp;
		ret+=tmp;a-=tmp;
		if(a==0)break;
	}
	return ret;
}
int work(vector<string>&bridges,int s1,int t1,int c1,int s2,int t2,int c2){
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
		if(bridges[i][j]=='X')g[i][j]=0;
		else if(bridges[i][j]=='O')g[i][j]=1;
		else g[i][j]=inf;//建图 
	s=n+1;t=s+1;
	g[s][s1]=g[t1][t]=c1;
	g[s][s2]=g[t2][t]=c2;//连接源汇 
	int ret=0;
	while(bfs())ret+=dfs(s,inf);//dinic
	return ret;
}
class OldBridges {
public:
	string isPossible(vector <string> bridges, int a1, int a2, int an, int b1, int b2, int bn) {
		n=bridges.size();
		return work(bridges,a1,a2,an,b1,b2,bn)==(an+bn)&&work(bridges,a1,a2,an,b2,b1,bn)==(an+bn)?"Yes":"No";
		//判断两次的流量是否都流满 
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
