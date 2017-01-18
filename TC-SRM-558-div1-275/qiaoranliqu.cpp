#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<cmath>
#include<string>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 100005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,R[N],G[N],B[N],X[N],cb,l,f[N];
int good(int x,int y) //判断这一段是否能够成为第一种颜色 
{
		if (max(R[y]-R[x],max(G[y]-G[x],B[y]-B[x]))+X[y]-X[x]==y-x) return 1;
		return 0;
}
int gao(int x,int y) //计算一段的代价 
{
	 return ((x+y-1)/y)*cb;
}
class Stamp
{
  public:
  	int getMinimumCost(string color, int A, int CostB)
  	{
  			cb=CostB;
  			n=color.size();
  			for (i=1;i<=n;++i)
  			  R[i]=R[i-1]+(color[i-1]=='R'),
  			  G[i]=G[i-1]+(color[i-1]=='G'),
  			  B[i]=B[i-1]+(color[i-1]=='B'),
  			  X[i]=X[i-1]+(color[i-1]=='*');
  			int ans=(int)1e9;
  			for (l=1;l<=n;++l) //枚举邮票的长度L 
  			{
  				memset(f,60,sizeof(f));
  				f[0]=0;
  				for (i=1;i<=n;++i) //枚举右端点 
  					for (j=l;j<=i;++j)
  						if (good(i-j,i))
  							f[i]=min(f[i],f[i-j]+gao(j,l));
  				ans=min(ans,f[n]+l*A);
  			}
  			return ans;
	} 
};

