#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>

#define N 2005

using namespace std;

const int Mo=(int)1e9+7;

vector<int>v[N];

int i,j,m,n,p,k,d=2001;

int f[N][N*2],g[N][N*2],F[N*2],G[N*2],H[N*2],ans,F1[N*2],G1[N*2],H1[N*2];

int fa[N],size[N];

void add(int x,int y) { v[x].push_back(y); } 

void jia(int &x,int y) { x+=y; if (x>=Mo) x-=Mo; }  

void dfs(int x) //假设要计算第一个人的期望,那么设其有x个连通块,y个点.那么代价下界就是2*(x-1)-y,易证明这个下界是可以到达的.
				//设f_{i,j},g_{i,j}表示i的子树中2*(x-1)-y的值是j,且当前点i选/不选的方案,通过f/g可以向上合并 
{	    
        int i,j,k;
        for (i=0;i<(int)v[x].size();++i)
	    {
	    	    int p=v[x][i];
	    	    if (fa[x]==p) continue;
	    	    fa[p]=x;
	    	    dfs(p);
	    }
	    memset(F,0,sizeof(F));
		memset(G,0,sizeof(G));
		memset(H,0,sizeof(H)); 
		F[d]=1;
		for (i=0;i<(int)v[x].size();++i)
		{
		        int p=v[x][i];
		        if (fa[x]==p) continue;
		        fa[p]=x;
		        memset(F1,0,sizeof(F1));
		        memset(G1,0,sizeof(G1));
		        memset(H1,0,sizeof(H1));
		        for (j=size[x]+d;j>=d-size[x];--j)
		          {
					long long now1=F[j],now2=G[j],now3=H[j];
				       for (k=size[p]+d;k>=d-size[p];--k)
					  {
					  	    jia(F1[j+k-d],1ll*now1*f[p][k]%Mo);
					  	    jia(G1[j+k-d],1ll*now1*g[p][k]%Mo);
					  	    jia(G1[j+k-d],1ll*now2*f[p][k]%Mo);
					  	    if (j+k-d-2>=0) jia(G1[j+k-d-2],1ll*now2*g[p][k]%Mo);
					  	    jia(H1[j+k-d],1ll*now1*g[p][k]%Mo);
					  	    jia(H1[j+k-d],1ll*now3*g[p][k]%Mo);
					  	    jia(H1[j+k-d],1ll*now3*f[p][k]%Mo); 
				      }
				  }
				size[x]+=size[p];
			   for (j=size[x]+d;j>=d-size[x];--j) F[j]=F1[j],G[j]=G1[j],H[j]=H1[j];
		}
	        for (j=size[x]+d;j>=d-size[x];--j)
		  {
		  	       jia(f[x][j],F[j]);
		  	       jia(f[x][j],H[j]);
		  	       jia(g[x][j+1],F[j]);
		  	       jia(g[x][j-1],G[j]);
	      }
	    size[x]++; 
}
class CentaurCompany{
	public:
		int getvalue(vector<int> x,vector<int> y)
		{
			    n=x.size()+1;
			    for (i=0;i<n-1;++i) 
				add(x[i],y[i]),add(y[i],x[i]);
			    dfs(1);
			    for (i=d+2;i<=d+n;++i) jia(ans,1ll*(f[1][i]+g[1][i])*(i-d-2)%Mo);
			    return 2*ans%Mo; //这是个对称的游戏,所以两个人期望相同,只要计算出其中一个*2即可. 
	    }
}ZYB;

int main()
{
	  freopen("1.in","r",stdin);
	  freopen("1.out","w",stdout);
	  scanf("%d",&n);
	  vector<int> v1,v2; int x,y;
	  for (i=1;i<n;++i)
	  {
	  	  scanf("%d%d",&x,&y);
	  	  v1.push_back(x); v2.push_back(y); 
	  }
	  printf("%d\n",ZYB.getvalue(v1,v2));
}
