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
#define pb push_back

#define N 105
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
const int inf=(int)1e9;
char c[M];
int i,j,m,n,p,k,ID[N],IN[N],ans,len,id[N][N],tot,pre[N],vis[N];
struct Node{int x,y,z;}B[M];
void add(int x,int y,int z)
{
	  B[++m]=(Node){x,y,z};
}
int Tree(int root)
{
	  int i,j,k,ans=0; n=tot;
	  for (;;)
	  {
	  	    for (i=1;i<=n;++i) IN[i]=inf,pre[i]=-1,ID[i]=-1,vis[i]=0;
	  	    IN[root]=0;
	  	    for (i=1;i<=m;++i)
	  	    {
	  	    	  if (B[i].x==B[i].y) continue;
	  	    	  if (B[i].y==root) continue;
	  	    	  if (B[i].z<IN[B[i].y]) 
	  	    	  { 
	  	    	     IN[B[i].y]=min(IN[B[i].y],B[i].z);
	  	    	     pre[B[i].y]=B[i].x;
				  }
	  	    }
	  	    for (i=1;i<=n;++i)
	  	       if (IN[i]==inf) return -1; 
	  	    int cnt=0;
	  	    for(i=1;i<=n;++i)
	  	    {
	  	    	    ans+=IN[i];
	  	    	    int v=i,u;
	  	    	    while (vis[v]!=i&&ID[v]==-1&&v!=root)
	  	    	       vis[v]=i,v=pre[v];
	  	    	    if (v!=root&&ID[v]==-1) 
	  	    	    {
	  	    	        for (++cnt,u=pre[v];u!=v;u=pre[u]) ID[u]=cnt;
	  	    	    ID[v]=cnt;
	  	    	    }
	  	    }
	  	    if (cnt==0) break;
            for (i=1;i<=n;++i) if (ID[i]==-1) ID[i]=++cnt; 
	  	    for (i=1;i<=m;++i)
	  	    {
	  	    	  int v=B[i].y;
	  	    	  B[i].x=ID[B[i].x];
	  	    	  B[i].y=ID[B[i].y];
	  	    	  if (B[i].x!=B[i].y) B[i].z-=IN[v];
			}
			n=cnt; root=ID[root];
	  }
	  return ans;
}
class FoxTheLinguist{
    public:
	int minimalHours(int nc,vector<string> s)
	{
		   tot=1;  n=nc;
		   for (i=0;i<n;++i)
		   {
		   	    for (j=0;j<=9;++j) id[i][j]=++tot; 
		   	    add(1,id[i][0],0);
		   	    for (j=9;j;--j) add(id[i][j],id[i][j-1],0);
		   }
		   len=0;
		   for (i=0;i<s.size();++i)
		   	   for (j=0;j<s[i].length();++j) c[++len]=s[i][j]; 
		   len=(len+1)/12;
		   for (i=1;i<=len;++i)
		   {
		   	    int rest=12*(i-1);
		        int Aa=c[rest+1]-'A',Ab=c[rest+2]-'0',Ba=c[rest+5]-'A',Bb=c[rest+6]-'0',
				cnt=(c[rest+8]-'0')*1000+(c[rest+9]-'0')*100+(c[rest+10]-'0')*10+(c[rest+11]-'0');
				add(id[Aa][Ab],id[Ba][Bb],cnt);
		   }
		   return Tree(1);
	}
}E;
int main()
{
	 vector<string> v;
     v.pb("A0->A9:1000 A0->A6:0300 A3->A9:0600");
	 printf("%d\n",E.minimalHours(1,v));
}
