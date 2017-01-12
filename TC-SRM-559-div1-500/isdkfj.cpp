#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
int n,fst[555],nxt[555],to[555],d[555],tt;
bool vis[55][55];
LL f[55][55];

LL dfs(int x,int y,int fa){//x:点，y:二叉树，fa:父亲 
	if(vis[x][y])return f[x][y];
	vis[x][y]=1;
	LL &ret=f[x][y];ret=0;
	vector<int>ch;
	for(int i=fst[x];i;i=nxt[i])if(to[i]!=fa)ch.push_back(to[i]);
	if(2*y==n)ret=ch.size()==1;//只有一个儿子 
	else if(y>n/2)ret=ch.size()==0;//没有儿子 
	else if(ch.size()==2)ret=dfs(ch[0],y*2,x)*dfs(ch[1],y*2+1,x)+dfs(ch[1],y*2,x)*dfs(ch[0],y*2+1,x);
	//dp 
	return ret;
}

class HatRack {
public:
	long long countWays(vector <int> knob1, vector <int> knob2) {
		n=knob1.size()+1;
		if(n==2)return 2;//特判 
		for(int i=0,x,y;i<knob1.size();++i){
			x=knob1[i],y=knob2[i];
			nxt[++tt]=fst[x];fst[x]=tt;to[tt]=y;
			nxt[++tt]=fst[y];fst[y]=tt;to[tt]=x;
			++d[x];++d[y];
		}
		for(int i=1;i<=n;++i)if(d[i]>3)return 0;//度数超过3不合法 
		LL ret=0;
		for(int i=1;i<=n;++i)if(d[i]==2){
			memset(vis,0,sizeof vis);
			ret+=dfs(i,1,0);//dp 
		}
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
