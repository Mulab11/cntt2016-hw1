#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;
typedef int Arr[6561];
const int M=1000000007;

class SimilarNames
{
	public:
	
	int n,m,p3[10],p5[10],fta[390625],ftb[390625];
	int ipx[55][55];
	vector<int> adj[55],A[55],B[55];
	int fa[55];
	
	Arr f[55],g,temp;
	
	int ispre(string a,string b)//check if a is a prefix of b.
	{
		if(a.size()>b.size())return 0;
		for(int i=0;i<a.size();i++)
			if(a[i]!=b[i])return 0;
		return 1;
	}
	
	void mult(Arr &a,Arr &b,Arr &c)//We use ternary subset convolution to merge the knapsack.
	{
		memset(temp,0,p3[m]<<2);
		for(int k=0;k<p5[m];k++)
		{
			int i=fta[k],j=ftb[k];
			temp[i+j]=(temp[i+j]+(LL)a[i]*b[j])%M;
		}
		for(int i=0;i<p3[m];i++)
			c[i]=temp[i];
	}
	
	int dp(int x)
	{
		//dp in the subtree
		for(int i=0;i<adj[x].size();i++)
			dp(adj[x][i]);
		//merge the knapsack
		memset(g,0,p3[m]<<2);
		g[0]=1;
		for(int y,i=0;i<adj[x].size();i++)
		{
			y=adj[x][i];
			mult(g,f[y],g);
		}
		for(int s=0,t,w;s<p3[m];s++)
			if(t=g[s])
			{
				(f[x][s]+=g[s])%=M;
				//place no index here
				for(int k=0;k<n;k++)//enumerate all index
					if(!A[k].empty()||!B[k].empty())
					{
						w=s;
						//get the new status w
						for(int i=0;w!=-1&&i<A[k].size();i++)
							if(w/p3[A[k][i]]%3!=0)
								w=-1;
							else
								w+=p3[A[k][i]];
						for(int i=0;w!=-1&&i<B[k].size();i++)
							if(w/p3[B[k][i]]%3!=1)
								w=-1;
							else
								w+=p3[B[k][i]];
						if(w!=-1)//we can place k here
							(f[x][w]+=g[s])%=M;
					}
			}
	}
	
	int count(vector<string> names,vector<int> info1,vector<int> info2)
	{
		m=info1.size();
		for(int i=0;i<info1.size();i++)
			B[info1[i]].push_back(i),
			A[info2[i]].push_back(i);
		//A[i] should be in B[i]'s subtree
		for(int i=p3[0]=1;i<=9;i++)p3[i]=p3[i-1]*3;
		for(int i=p5[0]=1;i<=9;i++)p5[i]=p5[i-1]*5;
		for(int i=0;i<p5[m];i++)
		{
			int a=0,b=0,t;
			for(int j=0;j<m;j++)
			{
				t=i/p5[j]%5;
				if(t==1)a+=p3[j];
				if(t==2)a+=p3[j]*2;
				if(t==3)b+=p3[j];
				if(t==4)b+=p3[j]*2;
			}
			fta[i]=a;
			ftb[i]=b;
		}
		//Make the trie.
		n=names.size();
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				ipx[i][j]=ispre(names[i],names[j]);
		memset(fa,-1,sizeof(fa));
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(i!=j&&ipx[i][j])
				{
					int flag=0;
					for(int k=0;k<n;k++)
						if(k!=i&&k!=j&&ipx[i][k]&&ipx[k][j])
							flag=1;
					if(!flag)
					{
						fa[j]=i;
						adj[i].push_back(j);
					}
				}
		//Dp on the trie
		//f[x][s] means the number og ways to place the index in subtree x when the status of info matching is s
		//s is a ternary number and for each ternary bit:
		//0 none of the names occurs
		//1 the second name occurs in the subtree
		//2 both the first and second words occur and the second is in the first's subtree
		for(int i=0;i<n;i++)
			if(fa[i]==-1)
				dp(i);
		memset(g,0,p3[m]<<2);
		g[0]=1;
		//merge the answer in all tries
		for(int i=0;i<n;i++)
			if(fa[i]==-1)
				mult(g,f[i],g);
		int ans=g[p3[m]-1],cnt=0;
		//We only consider the index which occur in info1 and info2, and we can arrange the left index freely
		//We need to multiply answer by cnt!
		for(int i=0;i<n;i++)
			if(A[i].empty()&&B[i].empty())
				cnt++;
		for(int i=1;i<=cnt;i++)
			ans=(LL)ans*i%M;
		return ans;
	}
};

