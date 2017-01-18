#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>

#define N 1005

using namespace std;
int i,j,m,n,p,k,dis[N],Q[N],l;
vector<int>v[N];
int bfs(int x)
{
	  memset(dis,-1,sizeof(dis));
	  dis[x]=0;
	  Q[Q[0]=1]=x;
	  for (l=1;l<=Q[0];++l)
	  {
	  	  int p=Q[l];
	  	  for (i=0;i<(int)v[p].size();++i) 
	  	    if (dis[v[p][i]]==-1)
	  	    {
	  	    	  dis[v[p][i]]=dis[p]+1;
	  	    	  Q[++Q[0]]=v[p][i];
	  	    }
	  }
	  int id=1;
	  for (i=1;i<=n;++i) if (dis[id]<dis[i]) id=i;
	  return id;
}
class TheTree{
	public:
		int maximumDiameter(vector<int> A)
	    {
		     int a=1,b=-1; n=1;
			 for (i=0;i<(int)A.size();++i) 
			 {
			 	     v[a].push_back(++n); v[n].push_back(a);
			 	     if (A[i]>=2)
			 	     {
			 	     	   if (b!=-1) v[b].push_back(++n),v[n].push_back(b); 
			 	     	   else v[a].push_back(++n),v[n].push_back(a);
			 	     	   a=n-1; b=n;
			 	     }
			 	     else a=n,b=-1;
			 }
			 a=bfs(1);
			 a=bfs(a);
			 return dis[a];
		}
};
