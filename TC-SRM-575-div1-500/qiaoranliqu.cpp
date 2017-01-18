#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>

#define N 3005
#define M 1000005

using namespace std;

double f[M][2],D[N],ans;
int A[N],i,n,j;
string s;

class TheSwapsDivOne{
	 public:
	 	double find(vector<string> v,int k)
	 	{
	 		    for (i=0;i<(int)v.size();++i) s+=v[i];
	 		    n=s.length();
			    for (i=1;i<=n;++i) A[i]=s[i-1]-'0';
				f[0][1]=1.;
				double di=1.*n*(n-1)/2.; di=1./di;
				for (i=1;i<=k;++i) //考虑一个点留在自己这个点方案和不留在自己这个点的期望,不留在自己点的而停留在其他某个点是等概率的 
				{
				   f[i][1]=f[i-1][1]*(1.-di*(n-1))+f[i-1][0]*di;
				   f[i][0]=f[i-1][1]*di*(n-1)+f[i-1][0]*(1-di);
			    }
				for (i=1;i<=n;++i) //对于每个位置,计算在每个点的答案 
				    for (j=1;j<=n;++j)
					  if (i!=j) 
					   D[i]+=1.*A[j]*f[k][0]/(n-1);
					   else D[i]+=1.*A[j]*f[k][1];
			    for (i=1;i<=n;++i)
				 ans+=1.*i*(n-i+1)*D[i];
				return ans/(n*(n+1)/2); 
		 }
};
