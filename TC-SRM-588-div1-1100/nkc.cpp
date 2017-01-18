#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 5010
#define pcan(x,y) (x>=0&&x<n&&y>=0&&y<m&&field[x][y]!='#')
using namespace std;
int dx[4]=
{0,0,1,-1},dy[4]=
{1,-1,0,0};
struct GameInDarknessDiv1
{
	int n,m,A,B;
	int to[N],nxt[N],pre[N],cnt;
	int da[N],db[N];
	void ae(int ff,int tt)
	{
		cnt++;
		to[cnt]=tt;
		nxt[cnt]=pre[ff];
		pre[ff]=cnt;
	}
	int c(int x,int y)
	{
		return x*m+y;
	}
	void dfs(int *S,int x,int fa)
	{
		if(fa!=-1) S[x]=S[fa]+1;
		int i,j;
		for(i=pre[x];i;i=nxt[i])
		{
			j=to[i];
			if(j==fa) continue;
			dfs(S,j,x);
		}
	}
	int DFS(int x,int fa)
	{
		int i,j,maxn=0;
		for(i=pre[x];i;i=nxt[i])
		{
			j=to[i];
			if(j==fa) continue;
			maxn=max(DFS(j,x),maxn);
		}
		return maxn+1;
	}
	bool judge(int x)
	{
		int i,j,tot=0;
		for(i=pre[x];i;i=nxt[i])
		{
			j=to[i];
			if(DFS(j,x)>=3) tot++;
		}
		return (tot>=3);
	}
	string check(vector <string> field)
	{
		n=field.size(),m=field[0].size();
		int i,j,k;
		for(i=0;i<n;i++)
		for(j=0;j<m;j++)
		if(field[i][j]!='#')
		{
			if(field[i][j]=='A') A=c(i,j);
			if(field[i][j]=='B') B=c(i,j);
			for(k=0;k<4;k++)
			if(pcan(i+dx[k],j+dy[k]))
			ae(c(i,j),c(i+dx[k],j+dy[k]));
		}
		dfs(da,A,-1);
		dfs(db,B,-1);
		for(i=0;i<n*m;i++)
		if(da[i]>=db[i]+2)
		if(judge(i)) return "Bob wins";
		return "Alice wins";
	}
};
/*GameInDarknessDiv1 P;
int main()
{
	vector<string>V;
	V.push_back("A.B..");
 	V.push_back(".#.#.");
 	V.push_back("#..##");
 	cout<<P.check(V);
}*/