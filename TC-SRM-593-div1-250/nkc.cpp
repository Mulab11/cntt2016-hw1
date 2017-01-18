#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define pcan(x,y) (x>=0&&x<n&&y>=0&&y<n&&board[x][y]=='X')
#define N 20010
using namespace std;
int dx[6]=
{-1,-1,0,0,1,1},dy[6]=
{0,1,-1,1,-1,0};
struct HexagonalBoard
{
	int to[N],nxt[N],pre[N],cnt;
	int n;
	void ae(int ff,int tt)
	{
		cnt++;
		to[cnt]=tt;
		nxt[cnt]=pre[ff];
		pre[ff]=cnt;
	}
	int c(int x,int y)
	{
		return x*n+y;
	}
	int col[N];
	bool dfs(int x,int C)
	{
		col[x]=C;
		int i,j;
		for(i=pre[x];i;i=nxt[i])
		{
			j=to[i];
			if(!col[j])
			{
				if(!dfs(j,3-C))
				return false;
			}
			else
			{
				if(col[j]==C)
				return false;
			}
		}
		return true;
	}
	bool p2()
	{
		int i;
		for(i=0;i<n*n;i++)
		if(!col[i])
		if(!dfs(i,1)) return false;
		return true;
	}
	int minColors(vector <string> board)
	{
		n=board.size();
		int i,j,k;
		bool F=false; 
		for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		if(board[i][j]=='X')
		{
			F=true;
			for(k=0;k<6;k++)
			if(pcan(i+dx[k],j+dy[k]))
			ae(c(i,j),c(i+dx[k],j+dy[k]));
		}
		if(!F) return 0;
		if(cnt==0) return 1;
		if(p2()) return 2;
		return 3;
	}
};