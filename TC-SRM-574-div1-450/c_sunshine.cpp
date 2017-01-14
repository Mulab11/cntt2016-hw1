#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;

class PolygonTraversal
{
	public:
	int n,m,st,L;
	int po[20];
	LL f[1<<18][18];
	
	LL dfs(int s,int p)
	{
		//f[s][p]: the set of visited vertices is s, and now it's at vertex p
		LL &r=f[s][p];
		if(~r)return r;
		if(s==L)return r=(p+1)%n!=po[0]&&(p+n-1)%n!=po[0];//if the last visited vertex is neat point[0], the path is invalid.
		r=0;
		for(int q=(p+1)%n,s1=0,s2=L^1<<p^1<<q;q!=p;s1^=1<<q,q=(q+1)%n,s2^=1<<q)//pick next vertex to go to
			if(!(s&1<<q)&&(s1&s)&&(s2&s))r+=dfs(s|1<<q,q);
		return r;
	}
	
	LL count(int N,vector<int> points)
	{
		n=N,m=points.size();
		memset(f,-1,sizeof(f));
		st=0;L=(1<<n)-1;
		for(int i=0;i<m;i++)
			st|=1<<(po[i]=points[i]-1);
		return dfs(st,po[m-1]);
	}
};

