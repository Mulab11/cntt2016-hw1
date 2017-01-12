#include <bits/stdc++.h>

using namespace std;

const int mpp=1594323;
int pw[14],f[mpp],mz,sb,mc;
bool vis[mpp],g[mpp];
struct orz{int x,y;}po[14];
bool bfs(int x,int y){//预处理是否可行 
	if(vis[x])return g[x];vis[x]=1;
	if(y==mz){//满了就判断 
		bool u[14]={0},v[14]={0};int res=0;
		for(int i=0,j=x,k;i<mz;++i){
			k=j%3;j/=3;
			if(k==2)u[po[i].x]^=1,v[po[i].y]^=1;
			else ++res;
		}
		g[x]=1;if(res!=mc)g[x]=0;
		for(int i=0;i<13;++i)if(u[i]||v[i])g[x]=0;
		return g[x];}
	for(int i=0,j=x,k;i<mz;++i){//没满就搜索 
		k=j%3;j/=3;
		if(k==0){
			if(bfs(x+pw[i],y+1))g[x]=1;
			if(bfs(x+2*pw[i],y+1))g[x]=1;
		}}return g[x];}
int dfs(int x,int y){//dp 
	if(vis[x])return f[x];vis[x]=1;
	if(y==sb)return 0;
	for(int i=0,j=x,k,l;i<mz;++i){
		k=j%3;j/=3;
		if(k==0){
			l=999999;
			if(g[x+pw[i]])l=min(l,dfs(x+pw[i],y+1)+1);
			if(g[x+2*pw[i]])l=min(l,dfs(x+2*pw[i],y+1));
			if(l!=999999&&l>f[x])f[x]=l; 
		}}return f[x];}


class MagicalHats {
public:
	int findMaximumReward(vector <string> board, vector <int> coins, int numGuesses) {
		pw[0]=1;for(int i=1;i<=13;++i)pw[i]=pw[i-1]*3;
		int n=board.size(),m=board[0].size();mc=coins.size();
		for(int i=0;i<n;++i)
			for(int j=0;j<m;++j)if(board[i][j]=='H'){
				po[mz].x=i;po[mz].y=j;mz++;}
		if(!bfs(0,0))return -1;//不符合就返回-1 
		sb=numGuesses;memset(vis,0,sizeof vis);//清空数组 
		int aaa=dfs(0,0);aaa=min(aaa,(int)coins.size()); 
		sort(coins.begin(),coins.end());int bbb=0;//排序 
		for(int i=0;i<aaa;++i)bbb+=coins[i];
		return bbb;
	}
};




//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
