// BEGIN CUT HERE

// END CUT HERE
#line 5 "HexagonalBoard.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;


class HexagonalBoard{
	struct edge{
		int adj,next;
		edge(){}
		edge(int _adj,int _next):adj(_adj),next(_next){}
	} e[23333];
	int n,g[6666],m;
	void AddEdge(int u,int v){
		e[++m]=edge(v,g[u]);g[u]=m;
		e[++m]=edge(u,g[v]);g[v]=m;
	}

	bool found;
	int col[6666];
	void dfs(int u){
		for (int i=g[u];i;i=e[i].next){
			int v=e[i].adj;
			if (col[v]<0){
				col[v]=col[u]^1;
				dfs(v);
			}
			else if (col[u]^col[v]^1){
				found=1;
				return;
			}
		}
	}

	int id[66][66];
	public:
	int minColors(vector <string> board){
		memset(id,0,sizeof(id));n=0;
		memset(g,0,sizeof(g));m=1;
		const int dx[3]={-1,-1,0};
		const int dy[3]={0,1,-1};
		for (int i=0;i<board.size();++i)
			for (int j=0;j<board[i].length();++j)if (board[i][j]=='X'){
				id[i+1][j+1]=++n;
				for (int k=0;k<3;++k)
					if (id[i+1+dx[k]][j+1+dy[k]])
						AddEdge(id[i+1][j+1],id[i+1+dx[k]][j+1+dy[k]]);
			}
		if (!n) return 0;
		if (m==1) return 1;
		memset(col,-1,sizeof(col));found=0;
		for (int i=1;i<=n&&!found;++i)if (col[i]<0){
			col[i]=0;
			dfs(i);
		}
		return found?3:2;
	}
};

//this is for test
/*
int main(){
	HexagonalBoard test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
