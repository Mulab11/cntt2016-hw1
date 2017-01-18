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

#define N 1000000
#define M 55
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,ans=(int)1e9,f[N*2],sum,tot;
class MayTheBestPetWin{
	public:
		int calc(vector<int> A,vector<int> B)
		{
			  n=A.size();
			  for (i=0;i<n;++i) sum+=A[i],A[i]+=B[i],tot+=A[i];
			  f[0]=1;
			  for (i=0;i<n;++i)
			    for (j=N;j>=0;--j) if (f[j]) f[j+A[i]]=1;
			  for (i=0;i<=N;++i)
			    if (f[i])
			    	    ans=min(ans,max(tot-i,i));
			  return ans-sum;
		}
}; 
