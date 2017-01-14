#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
const int dx[6]={-1,-1,0,0,1,1};
const int dy[6]={0,1,-1,1,-1,0};
class HexagonalBoard
{
	public:
	int n,m,f1,f2,f3;
	vector<string> s;
	int c[55][55];
	
	void dfs(int x,int y,int t)//depth first search
	{
		if(c[x][y])
		{
			if(c[x][y]!=t)f3=1;
			return;
		}
		c[x][y]=t;
		for(int xx,yy,k=0;k<6;k++)
		{
			xx=x+dx[k];
			yy=y+dy[k];
			if(xx>=0&&xx<n&&yy>=0&&yy<m&&s[xx][yy]=='X')
				dfs(xx,yy,t^3);
		}
	}
	
	int minColors(vector<string> board)
	{
		//We can always color the board with no more than 3 colors
		//f1: the board can't be colored with less than 1 color
		//f2: the board can't be colored with less than 2 colors
		//f3: the board can't be colored with less than 3 colors
		n=board.size();
		m=board[0].size();
		s=board;
		f1=f2=f3=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(s[i][j]=='X')
				{
					f1=1;
					//if there is a pair of adjacent cells, f2=1. 
					if(j+1<m&&s[i][j+1]=='X')
					{
						f2=1;
					}
					if(i+1<n&&s[i+1][j]=='X')
						f2=1;
					if(i+1<n&&j-1>=0&&s[i+1][j-1]=='X')
						f2=1;
					if(!c[i][j])//use depth first search to determine if it is a bipartite graph
						dfs(i,j,1);
				}
		return f1+f2+f3;
	}
};

