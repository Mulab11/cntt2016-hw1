#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
const int dx[4]={0,0,-1,1},dy[4]={-1,1,0,0},inf=(1<<25)-1;

template<class T> inline bool ten(T &x,const T &y){return y<x?x=y,1:0;}
template<class T> inline bool rel(T &x,const T &y){return x<y?x=y,1:0;}

class Tunnels
{
	public:
	int n,m,cnt;
	char s[55][55];
	int col[55][55],deg[55][55],Hl[2555],Hh[2555];
	int Lu[55],Ld[55],Ru[55],Rd[55],LR[55];
	int f[55][55][55];
	
	void tdfs(int x,int y,int id)//Depth first search to find the connected components.
	{
		if(x<1||x>n||y<1||y>m||col[x][y]!=-1||s[x][y]!='X')return;
		col[x][y]=id;
		for(int i=0;i<4;i++)
			tdfs(x+dx[i],y+dy[i],id);
	}
	
	int dp()
	{
		//f[p][i][j] :the most number of matching we can make if we are at p-th row,
		//and there are i tunnels on the left and j tunnels on the right which haven't been matched.
		for(int i=0;i<=n;i++)
			for(int j=0;j<=n;j++)
				f[n+1][i][j]=-inf;
		f[n+1][0][0]=0;
		for(int p=n;p;p--)
			for(int i=0;i<=p;i++)
				for(int j=0;j<=p;j++)
				{
					int a,b;
					f[p][i][j]=-inf;
					//a,b =
					//-1 : match a tunnel
					// 0 : do nothing
					// 1 : create a new tunnel that hasn't been matched.
					for(a=-1;a<=1;a++)
						for(b=-1;b<=1;b++)
						{
							if( (a!= 1||Ld[p])
								&&(a!=-1||Lu[p])
								&&(b!= 1||Rd[p])
								&&(b!=-1||Ru[p])
								&&(a== 0||a!=b||!LR[p]) 
								&&(i+a>=0&&j+b>=0)
								)
								rel(f[p][i][j],(a==1)+(b==1)+f[p+1][i+a][j+b]);
						}
				}
		return f[1][0][0];
	}
	
	int minimumTunnels(vector<string> frame)
	{
		n=frame.size();m=frame[0].size();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				s[i][j]=frame[i-1][j-1];
		memset(col,-1,sizeof(col));
		//Get all connected components and degrees.
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				if(col[i][j]==-1&&s[i][j]=='X')
					tdfs(i,j,++cnt);
				for(int k=0;k<4;k++)
					deg[i][j]+=(s[i+dx[k]][j+dy[k]]=='X');
			}
		if(m==1)return cnt>0;//Only one rows.
		//Get each connected component's height range [Hl,Hr]
		for(int i=1;i<=cnt;i++)
			Hl[i]=n+1,Hh[i]=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(col[i][j]!=-1)
					ten(Hl[col[i][j]],i),rel(Hh[col[i][j]],i);
		//Lu[i] is true if the left-most cell of row i can be connected upwards.
		//Ld[i] is true if the left-most cell of row i can be connected downwards.
		for(int t,i=1;i<=n;i++)
			if(s[i][1]=='X'&&deg[i][1]<=1)
			{
				t=col[i][1];
				Lu[i]=(i==Hl[t]);
				Ld[i]=(i==Hh[t]);
			}
		//to avoid
		//x...
		//xX..
		//xX..
		//x...
		for(int i=2;i<n;i++)
			Ld[i+1]&=!Lu[i];
		//Ru[i] is true if the right-most cell of row i can be connected upwards.
		//Rd[i] is true if the right-most cell of row i can be connected downwards.
		for(int t,i=1;i<=n;i++)
			if(s[i][m]=='X'&&deg[i][m]<=1)
			{
				t=col[i][m];
				Ru[i]=(i==Hl[t]);
				Rd[i]=(i==Hh[t]);
			}
		//to avoid
		//...x
		//..Xx
		//..Xx
		//...x
		for(int i=2;i<n;i++)
			Rd[i+1]&=!Ru[i];
		//LR[i] is true if the i-th row is completely full.
		for(int i=1;i<=n;i++)
			LR[i]=(col[i][1]==col[i][m]&&col[i][1]!=-1);
		//A component has only one cell on the border, it can only be connected upwards.
		for(int i=2;i<=n;i++)
		{
			int t1=col[i][1],t2=col[i][m];
			if(t1!=t2)
			{
				if(t1!=-1&&Hl[t1]==Hh[t1])Ld[i]=0;
				if(t2!=-1&&Hl[t2]==Hh[t2])Rd[i]=0;
			}
		}
		return cnt-dp();
	}
};

