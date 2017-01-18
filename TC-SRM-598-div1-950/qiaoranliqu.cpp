#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair

#define N 55
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
const int inf=(int)1e9;
vector<int>v[N];
int i,j,m,n,p,k,f[N],g[N],fa[N];
void dfs(int x)
{
	   int i;
	   for (i=0;i<(int)v[x].size();++i)
	   {
	   	  int p=v[x][i];
	   	  if (fa[x]==p) continue;
	   	  fa[p]=x; dfs(p);
	   }
	   if (((int)v[x].size()-(fa[x]>-1))<=1)
	   {
	   	      f[x]=0;
	   	      for (i=0;i<(int)v[x].size();++i)
	   	      {
	   	      	   int p=v[x][i];
	   	      	   if (fa[x]==p) continue;
	   	      	   f[x]=f[p];
	   	      }
	   }
	   else f[x]=inf;
	   	   if (((int)v[x].size()-(fa[x]>-1))==0)
	   {
	   	    g[x]=1;
	   }
	      if (((int)v[x].size()-(fa[x]>-1))==1)
	      {
	      	  for (i=0;i<(int)v[x].size();++i)
	      	  {
	      	  	    int p=v[x][i];
	      	  	    if (fa[x]==p) continue;
	      	  	    g[x]=g[p];
	      	  }
	      	  return;
	      }
	   int Min=0;
	   for (i=0;i<(int)v[x].size();++i)
	   {
	   	     int p=v[x][i];
	   	     if (fa[x]==p) continue;
	   	     g[x]+=g[p];
	   	     Min=min(Min,f[p]-g[p]);
	   }
	   g[x]+=Min;
}
void add(int x,int y)
{
 v[x].push_back(y);
 v[y].push_back(x);
}
class TPS{
public:
int minimalBeacons(vector<string> s)
{ 
 //  n=5; add(0,1); add(1,2);add(2,3); add(2,4); 
     n=s.size();
     if (n==1) return 0;
     for (i=0;i<n;++i) 
       for (j=0;j<n;++j) if (s[i][j]=='Y') v[i].push_back(j);
     int Ans=(int)1e9; 
     for (i=0;i<n;++i)
     {
     	   memset(f,0,sizeof(f));
     	   memset(g,0,sizeof(g));
     	   memset(fa,-1,sizeof(fa));
     	   dfs(i);
     	   Ans=min(Ans,min(f[i],g[i])+1);
     }
     return Ans;
}
}FFT;
string s;
int main()
{
       vector<string> v;
       int n;
       scanf("%d",&n);
       for (i=0;i<n;++i) cin>>s,v.push_back(s);
       printf("%d\n",FFT.minimalBeacons(v));
}

