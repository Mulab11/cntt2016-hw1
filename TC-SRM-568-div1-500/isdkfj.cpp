#include <bits/stdc++.h>

using namespace std;

const int mo=1000000007;
int g[105][105],n,v[105];
bool vis[105],vv[105];

pair<int,int> dfs(int x,int y){//x填上y 
	vis[x]=1;vv[x]=1;v[x]=y;
	pair<int,int>ret,tmp;ret.first=y>=0;ret.second=x<n&&y==0;
	//first：是否满足条件 second：是否有0 
	for(int i=0;i<2*n;++i)if(g[x][i]!=-1){
		if(!vv[i]){//没被访问 
			tmp=dfs(i,g[x][i]-y);
			ret.first&=tmp.first;
			ret.second|=tmp.second;
		}
		else ret.first&=g[x][i]-y==v[i];//访问了判一下 
	}
	return ret;
}

class EqualSums {
public:
	int count(vector <string> board) {
		n=board.size();memset(g,-1,sizeof g);
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)if(board[i][j]!='-')
			g[i][j+n]=g[j+n][i]=board[i][j]-48;
		long long ans1=1,ans2=1;
		for(int i=0;i<n;++i)if(!vis[i]){
			int tmp1=0,tmp2=0;
			for(int j=0;j<=9;++j){
				memset(vv,0,sizeof vv);
				pair<int,int>k=dfs(i,j);
				tmp1+=k.first;if(!k.second)tmp2+=k.first;
			}
			ans1=ans1*tmp1%mo;
			ans2=ans2*tmp2%mo;
		}
		return (ans1-ans2+mo)%mo;//全部扣掉没0的 
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
