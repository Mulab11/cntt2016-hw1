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

#define N 55
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,vis[N],b[N],l;
long long f[N][N][N],ans,C[N][N];
void jia(long long &x,long long y) { x+=y; if (x>=Mo) x-=Mo; }
vector<int> v[N];
class Excavations{
	public:
		long long count(vector<int> kind,vector<int> depth,vector<int> found,int K)
		{
			   for (i=0;i<=50;++i)
			   {
			   	  C[i][0]=1;
			   	  for (j=1;j<=i;++j) C[i][j]=(C[i-1][j]+C[i-1][j-1]);
               }
			   n=depth.size(); m=found.size();
			   K-=m;
			   for (i=0;i<m;++i) vis[found[i]]=i+1; 
			   for (i=0;i<n;++i) b[i+1]=depth[i];
			   sort(b+1,b+n+1); b[0]=unique(b+1,b+n+1)-(b+1); 
			   for (i=0;i<n;++i)
			   {
			       depth[i]=lower_bound(b+1,b+b[0]+1,depth[i])-b;
				   v[vis[kind[i]]].push_back(depth[i]);
			   }
			   for (i=1;i<=m;++i) sort(v[i].begin(),v[i].end());	   
			   f[0][0][0]=1;
			   for (i=1;i<=m;++i)
			     for (j=0;j<=n;++j)
			       for (k=0;k<=n;++k)
			         if (f[i-1][j][k])
			         {
			         	  int p=v[i].size();
					      for (l=0;l<p;++l)
						     f[i][max(j,v[i][l])][k+(p-l-1)]+=f[i-1][j][k];
					 }
				for (i=0;i<=n;++i)
				  for (j=0;j<=n;++j)
				      if (f[m][i][j])
				      {
				      	  int sum=0;
				      	  for (k=0;k<v[0].size();++k) if (v[0][k]>i) ++sum;
				      	  ans+=1ll*f[m][i][j]*C[j+sum][K];
				      }
				return ans;
		} 
}E;
int main()
{
	vector<int> A,B,C; A.pb(1); A.pb(1); A.pb(2);A.pb(2);
	B.pb(10); B.pb(15); B.pb(10); B.pb(20);
	C.pb(1);
	E.count(A,B,C,2);
}

