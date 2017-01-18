#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<iostream>

using namespace std;

#define N 55
#define M 16

const int Mo=(int)1e9+7;
int n,f[N][1<<M],A[N],B[N],Q[N],size[N],fa[N],i,j,R[N],m,could[1<<M],Big[1<<M],G[1<<M];
vector<int>v[N],vec[N],gg[1<<M];
void bfs()
{
	  Q[0]=1;
	  int i,j,k,l;
	  for (l=1;l<=Q[0];++l)
	  {
	  	  int p=Q[l];
	  	  for (i=0;i<(int)v[p].size();++i)
		  {
		          int k=v[p][i];
				  --size[k];
				  if (!size[k]) fa[k]=p,Q[++Q[0]]=k,vec[p].push_back(k);
		  }
	  }
}
bool check(string a,string b)
{
	  if (a.length()>b.length()) return 0;
	  int i;
	  for (i=0;i<a.length();++i) if (a[i]!=b[i]) return 0;
	  return 1;

}
void pre()
{
	   int i,j,k;
	   for (i=0;i<(1<<R[0]);++i)
	   {
	   	       for (j=1;j<=m;++j) 
	   	       {
	   	       	    if (((1<<A[j])&i)&&((1<<B[j])&i)) continue;
				    if ((((1<<A[j])&i)==0)&&(((1<<B[j])&i)==0)) continue;
				    if ((((1<<A[j])&i)==0)&&(((1<<B[j])&i))) continue;
					break; 
		       }
		       if (j>m) could[++could[0]]=i,Big[i]=could[0];
	   }
	   for (i=1;i<=could[0];++i)
	   {
	   	       for (j=could[i];;j=(j-1)&could[i])
	   	       {
	   	       	    if (!Big[j]||!Big[could[i]^j]) continue;
	   	       	    for (k=1;k<=m;++k)
	   	       	    {
	   	       	    	if ((could[i]&(1<<A[k]))&&(could[i]&(1<<B[k])))
					    {
					    	    if ((j&(1<<A[k]))&&(j&(1<<B[k]))||((j&(1<<A[k]))==0)&&((j&(1<<B[k]))==0)) continue;
					    }
					    if (((could[i]&(1<<A[k]))==0)&&((could[i]&(1<<B[k]))==0)) continue;
					    if (((could[i]&(1<<A[k]))==0)&&((could[i]&(1<<B[k])))) continue;
					    break;
					}
					if (k>m) gg[i].push_back(Big[j]);
					if (j==0) break;
			   }
	   }
}
int fac(int x)
{
	  int i,sum=1;
	  for (i=1;i<=x;++i) sum=1ll*sum*i%Mo;
	  return sum;
}
void jia(int &x,int y)
{
	x+=y; if (x>=Mo) x-=Mo;
}
void dfs(int x)
{
	int i,j,k;
	f[x][1]=1;
	for (i=0;i<(int)vec[x].size();++i)
	{
		   int p=vec[x][i];
		   dfs(p);
		   memset(G,0,sizeof(G));
		   for (j=could[0];j;--j)
		      for (k=0;k<(int)gg[j].size();++k)
		        jia(G[j],1ll*f[x][Big[could[j]^could[gg[j][k]]]]*f[p][gg[j][k]]%Mo);
		   for (j=1;j<=could[0];++j) f[x][j]=G[j];
	}
	if (x!=0) 
	for (i=could[0];i;--i)
	  for (j=0;j<R[0];++j)
	    if (!(could[i]&(1<<j))&&Big[could[i]|(1<<j)]) jia(f[x][Big[could[i]|(1<<j)]],f[x][i]);
}
class SimilarNames{
  public:
  int count(vector<string> name,vector<int> E,vector<int> F)
  {
  	   n=name.size(); m=E.size();
  	   for (i=1;i<=E.size();++i) A[i]=E[i-1],B[i]=F[i-1],R[++R[0]]=A[i],R[++R[0]]=B[i];
  	   sort(R+1,R+R[0]+1); R[0]=unique(R+1,R+R[0]+1)-(R+1);
	   for (i=1;i<=E.size();++i) A[i]=lower_bound(R+1,R+R[0]+1,A[i])-(R+1),B[i]=lower_bound(R+1,R+R[0]+1,B[i])-(R+1);
  	   for (i=1;i<=n;++i)
  	     for (j=1;j<=n;++j) if (i!=j&&check(name[i-1],name[j-1])) v[i].push_back(j),size[j]++;
	   for (i=1;i<=n;++i) if (!size[i]) v[0].push_back(i),++size[i];
	   bfs();
	   pre();
	   dfs(0);
	   return 1ll*f[0][could[0]]*fac(n-R[0])%Mo; 
  }
}ETT;
string s;
int main()
{
  scanf("%d%d",&n,&m); int x,y;
  vector<string> a;
  vector<int> b;
  vector<int> c;
  for (i=1;i<=n;++i) cin>>s,a.push_back(s);
  for (i=1;i<=m;++i) 
  {
  	   scanf("%d%d",&x,&y);
  	   b.push_back(x);
  	   c.push_back(y);
  }
  printf("%d\n",ETT.count(a,b,c));
}
