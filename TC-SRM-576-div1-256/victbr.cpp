#include <bits/stdc++.h>

using namespace std;

const int N = 50+10;

struct Node{
	int x,y,z;
	Node(){}
	Node(int x,int y,int z):x(x),y(y),z(z){}
};
bool operator < (const Node &a,const Node &b){
	return a.z < b.z;
}

class ArcadeManao{
	public:
		int fa[N*N],n,m,len,S,T;
		Node nod[N*N<<1];
		int shortestLadder(vector <string> level, int coinRow, int coinColumn){//最小生成树 
			n = level.size();
			m = level[0].size();
			S = cal(n-1,0);T = cal(coinRow-1,coinColumn-1);//起点在(n-1,0) 
			for (int i = 0;i < n;i++)
				for (int j = 0;j < m;j++)
					fa[cal(i,j)] = cal(i,j);
			for (int i = 0;i < n;i++)
				for (int j = 0;j+1 < m;j++)
					if (level[i][j] == 'X' && level[i][j+1] == 'X')
						 nod[++len] = Node(cal(i,j),cal(i,j+1),0);
					
			for (int i = 0;i < m;i++){
				int last = n-1;
				for (int j = n-2;j >= 0;j--)
					if (level[j][i] == 'X'){
						nod[++len] = Node(cal(j,i),cal(last,i),last-j);
						last = j;
					}
			}
			sort(nod+1,nod+1+len);
			for (int i = 1;i <= len;i++){
				int x = nod[i].x,y = nod[i].y;
				fa[x] = getfa(fa[x]);
				fa[y] = getfa(fa[y]);
				if (fa[x] != fa[y]) fa[fa[x]] = fa[y];
				fa[T] = getfa(fa[T]);
				fa[S] = getfa(fa[S]);
				if (fa[S] == fa[T])return nod[i].z;
			}
			return 0;
		}
		int cal(int x,int y){
			return x*m+y+1;
		}
		int getfa(int p){
			if (fa[p] == p) return p;
			fa[p] = getfa(fa[p]);
			return fa[p];
		}
};
