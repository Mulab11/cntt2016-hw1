#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN=1020,MAXM=15000,inf=1000000;
struct edge
{
	int u,v,w;
	edge(int _u=0,int _v=0,int _w=0):u(_u),v(_v),w(_w){}
}e[MAXM];
class FoxTheLinguist
{
	public:

int n,m;

inline int solve()//Directed Minimum Spanning Tree
{
	static int in[MAXN],pre[MAXN],inp[MAXN],vis[MAXN];
	int ans=0,root=n;
	while(true)
	{
		fill(in+1,in+n+1,inf);
		in[root]=0;
		for(int i=0;i<m;i++)
			if(e[i].u!=e[i].v&&e[i].w<in[e[i].v])in[e[i].v]=e[i].w,pre[e[i].v]=e[i].u;
		int cnt=0;
		fill(vis+1,vis+n+1,0);
		fill(inp+1,inp+n+1,0);
		for(int i=1;i<=n;i++)
		{
			ans+=in[i];
			int j;
			for(j=i;j!=root&&vis[j]!=i&&!inp[j];j=pre[j])vis[j]=i;
			if(j!=root&&!inp[j])
			{
				cnt++;
				for(;!inp[j];j=pre[j])inp[j]=cnt;
			}
		}
		if(!cnt)break;
		for(int i=1;i<=n;i++)
			if(!inp[i])inp[i]=++cnt;
		for(int i=0;i<m;i++)e[i].w-=in[e[i].v],e[i].u=inp[e[i].u],e[i].v=inp[e[i].v];
		n=cnt,root=inp[root];
	}
	return ans;
}

	char ID[256][256]; 
	
	int minimalHours(int n,vector<string> courseInfo)
	{
		this->n=n*10+1;
		int S=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<10;j++)
				ID['A'+i]['0'+j]=++S;
		S++;
		string ss;
		for(int i=0;i<courseInfo.size();i++)
			ss+=courseInfo[i];
		string ts="";
		vector<string> Info;
		for(int i=0;i<ss.size();i++)
			if(ss[i]==' ')
			{
				Info.push_back(ts);
				ts="";
			}
			else ts+=ss[i];
		Info.push_back(ts);
		//Above is dealing with the input data
		for(int i=0;i<Info.size();i++)
		{
			string t=Info[i];
			int u,v,w;
			u=ID[(int)t[0]][(int)t[1]];
			v=ID[(int)t[4]][(int)t[5]];
			w=0;
			for(int k=7;k<t.size();k++)
				w=w*10+t[k]-'0';
			e[m++]=edge(u,v,w);//add the edges from the prerequisite language to the target language
		}
		for(int i=0;i<n;i++)
		{
			e[m++]=edge(S,ID[(int)'A'+i][(int)'0'],0);//add the edge from S to X[0] 
			for(int j=1;j<10;j++)//add ehd edges from X[k+1] to X[k]
				e[m++]=edge(ID[(int)'A'+i][(int)'0'+j],ID[(int)'A'+i][(int)'0'+j-1],0);
		}
		int ans=solve();
		if(ans<1000000)return ans;
		return -1;
	}
};

