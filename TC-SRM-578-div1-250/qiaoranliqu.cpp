#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<string>

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
#define Mo 1000000007

using namespace std;
int i,j,m,n,p,k,f[N*N],l,size[N*N],ans,g[N*N];

int get(int x) { return f[x]==x?x:f[x]=get(f[x]); }

int ID(int x,int y) { return x*m+y; }
class GooseInZooDivOne{
	  public:
	  	int count(vector<string> v,int dis)
	  	{
	  		    n=v.size(); m=v[0].length();
	  		    int lim=ID(n-1,m-1);
	  		    for (i=0;i<=lim;++i) f[i]=i; 
	  		    for (i=0;i<n;++i) //考虑在距离不超过dis的点之间连一条边,这样会构成很多联通块,每个联通块要么不选,否则就要全选 
	  		      for (j=0;j<m;++j) 
	  		        if (v[i][j]=='v')
	  		        {
	  		          for (k=0;k<n;++k)
	  		            for (l=0;l<m;++l)
	  		              if (v[k][l]=='v'&&abs(i-k)+abs(j-l)<=dis)
	  		                f[get(ID(i,j))]=get(ID(k,l));
	  		        }
	  		        else size[ID(i,j)]--;
	  		    for (i=0;i<=lim;++i) size[get(i)]++;
	  		    g[0]=1;
	  		    for (i=0;i<=lim;++i) if(get(i)==i&&size[i]) //背包计算答案. 
	  		      for (j=lim+1;j>=size[i];--j) (g[j]+=g[j-size[i]])%=Mo;
	  		    for (i=2;i<=lim+1;i+=2) (ans+=g[i])%=Mo;
	  		    return ans;
	    }
}E;
int main()
{
	  vector<string> A;
	  A.push_back("vv");
	  printf("%d\n",E.count(A,1));
}
