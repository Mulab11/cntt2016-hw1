#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#define next next_
using namespace std;

const int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};

	char s[55][55];
	int I[55][55];
	
	int M,N,K;
	int pot[2555];
	
	int head[2555],adj[2555*4],next[2555*4],tot;
	int fa[2555];
	
	int dis[2555][2555],g[2555][2555];
	
	double f1[305],f2[305];

class Orienteering
{
	public:
	int R,C;
	
	inline void addedge(const int &u,const int &v)
	{tot++;adj[tot]=v;next[tot]=head[u];head[u]=tot;}
	
	void tdfs(int x,int r,int dp)
	{
		dis[r][x]=dp;
		for(int i=head[x];i;i=next[i])
			if(adj[i]!=fa[x])
				fa[adj[i]]=x,tdfs(adj[i],r,dp+1);
	}
	
	double work()
	{
		for(int i=1;i<=M;i++)
			fa[i]=0,tdfs(i,i,0);
		double Et=0,Ed=0;
		//E(steiner tree)
		f1[N]=1;
		for(int i=N-1;i>=0;i--)
			f1[i]=f1[i+1]/(i+1.)*(i+1.-K);
		for(int i=1,j,k,cnt;i<=M;i++)
			if(j=fa[i])
			{
				//For each edge calculate the possibility that it belongs to the steiner tree.
				cnt=0;
				//Count the nodes that on one side of the edge.
				for(k=1;k<=N;k++)
					cnt+=dis[i][pot[k]]>dis[j][pot[k]];
				Et+=(1.-f1[cnt]-f1[N-cnt]);//1 - the possibility at all selected special nodes are only on one side.
			}
		//E(diameter)
		for(int i=1;i<=N;i++)
			for(int j=1;j<=N;j++)
				g[i][j]=dis[pot[i]][pot[j]];
		f2[N-2]=1.;
		for(int i=N-3;i>=0;i--)
			f2[i]=f2[i+1]/(i+1.)*(i+1.-K+2);
		for(int i=1,j,k,cnt;i<=N;i++)
			for(j=i+1;j<=N;j++)
			{
				//For each pair (i,j), determine the possobility that the diameter is (i,j).
				cnt=0;
				//Count the nodes "k"s that (i,k) or (j,k) will be a better diameter than (i,j).
				for(k=1;k<=N;k++)
					if(k!=i&&k!=j)
					{
						//We only consider the diameter with the least lexicographical order.
						if(g[i][k]>g[i][j]||g[i][k]==g[i][j]&&k<j)continue;
						if(g[k][j]>g[i][j]||g[k][j]==g[i][j]&&k<i)continue;
						cnt++;
					}
				//These nodes cannot be selected.
				Ed+=g[i][j]*f2[cnt];
			}
		Ed*=(double)K*(K-1.)/N/(N-1.);
		//E(path)=2E(steiner tree)-E(diameter)
		return Et*2.-Ed;
	}
	
	double expectedLength(vector<string> field,int KK)
	{
		K=KK;
		R=field.size(),C=field[0].size();
		//Build the tree.
	 	for(int i=1;i<=R;i++)
		for(int j=1;j<=C;j++)
		{
			s[i][j]=field[i-1][j-1];
			if(s[i][j]!='#')
				{
					I[i][j]=++M;
					if(s[i][j]=='*')pot[++N]=M;
				}
		}
		for(int i=1;i<=R;i++)
			for(int j=1;j<=C;j++)
				if(I[i][j])
				{
  				int x,y;
  				for(int k=0;k<4;k++)
  				{
  					x=i+dx[k],y=j+dy[k];
  					if(I[x][y])addedge(I[i][j],I[x][y]);
					}
				}
		return work();
	}
};

