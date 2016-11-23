#include<cstdio>
#include<cstring>
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
const int mov[4][2]={{0,1},{-1,0},{0,-1},{1,0}};

class RotatingBot{
	static const int maxn=55;
	bool vis[maxn][maxn];
	
	bool check(int w,int h,int x,int y,vector<int> &t){
//		printf("check(%d,%d)\n",w,h);
		int n=t.size();
		memset(vis,0,sizeof(vis));
		vis[x][y]=true;
		for (int i=0;i<n;++i){
			for (int j=0;j<t[i];++j){
				x+=mov[i%4][0];
				y+=mov[i%4][1];
//				printf("x=%d,y=%d\n",x,y);
				if (x<=0||y<=0||x>h||y>w) return false;
				if (vis[x][y]) return false;
				vis[x][y]=true;
			}
			if (i!=n-1){
				int tx=x+mov[i%4][0],ty=y+mov[i%4][1];
				if (tx>0&&tx<=h&&ty>0&&ty<=w&&!vis[tx][ty]) return false;
			}
		}
		return true;
	}
	
	public:
	int minArea(vector<int> moves){
		int x,y,t=moves.size(),w,h;
		if (t>=4){
			h=max(moves[1],moves[3])+1;
			w=max(moves[0],moves[2])+1;
			x=moves[1]+1;
			y=w-moves[0];
		}
		else if (t==3){
			h=moves[1]+1;
			w=max(moves[0],moves[2])+1;
			x=h;
			y=w-moves[0];
		}
		else if (t==2){
			h=moves[1]+1;
			w=moves[0]+1;
			x=h;
			y=1;
		}
		else{
			h=1;
			w=moves[0]+1;
			x=1;
			y=1;
		}
		if (check(w,h,x,y,moves)) return w*h;
		else return -1;
	}
};
