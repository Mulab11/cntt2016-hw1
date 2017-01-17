#include<bits/stdc++.h>
#define LL long long
using namespace std;
int i,N,n,e[55][55],s[55];LL S;
class HatRack
{
	public:
		void dfs(int x,int f){int y=n;for(s[x]=1;y;y--)if(e[x][y]&&y^f)dfs(y,x),s[x]+=s[y];}
		LL calc(int x,int f,int k)
		{
			int c[55],t=0,y=n;LL r=1;
			for(N=max(N,k);y;y--)if(e[x][y]&&y^f)c[t++]=y;
			if(t>2)return 0;
			if(t>1)if(r*=s[c[0]]==s[c[1]]?2:1,s[c[0]]<s[c[1]])swap(c[0],c[1]);
			for(y=0;y<t;y++)r*=calc(c[y],x,k*2+y);
			return r;
		}
		LL countWays(vector<int> u,vector<int> v)
		{
			for(n=u.size()+1;i<n-1;i++)e[u[i]][v[i]]=e[v[i]][u[i]]=1;
			for(i=n;i;i--)dfs(i,0),S+=calc(i,0,N=1)*(N==n);
			return S;
		}
};
