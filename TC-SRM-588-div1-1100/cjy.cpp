#include<bits/stdc++.h>
#define ID(i,j) (i)*m+j
using namespace std;
int n,m,h[3000],e[6000],l[6000],i,j,d[3000],g[3000],s[3000],t,A,B;
void add(int x,int y){e[++t]=y,l[t]=h[x],h[x]=t,e[++t]=x,l[t]=h[y],h[y]=t;}
int dfs(int x,int f)
{
	d[x]=d[f]+1;
	g[x]=1;
	s[x]=0;
	for(int i=h[x];i;i=l[i])if(e[i]!=f)
	{
		dfs(e[i],x);
		g[x]=max(g[x],g[e[i]]+1);
		s[x]+=g[e[i]]>2;
	}
	if(x==ID(i,j))return s[x]>2;
}
class GameInDarknessDiv1
{
	public:
		string check(vector<string> s)
		{
			n=s.size();m=s[0].size();
			for(i=0;i<n;i++)for(j=0;j<m;j++)
			{
				if(s[i][j]=='A')A=ID(i,j);
				if(s[i][j]=='B')B=ID(i,j);
				if(s[i][j]!='#')
				{
					if(i&&s[i-1][j]!='#')add(ID(i,j),ID(i-1,j));
					if(j&&s[i][j-1]!='#')add(ID(i,j),ID(i,j-1));
				}
			}
			for(i=0;i<n;i++)for(j=0;j<m;j++)if(s[i][j]!='#'&&dfs(ID(i,j),0)&&d[A]>d[B]+1)return"Bob wins";
			return"Alice wins";
		}
};
