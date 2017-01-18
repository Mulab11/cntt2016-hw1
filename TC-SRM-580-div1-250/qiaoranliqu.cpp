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
int i,j,m,n,p,k,ans,A[N];
class EelAndRabbit{
	public:
		int getmax(vector <int> l, vector <int> t)
		{
			  n=l.size();
			  for (i=0;i<n;++i)
			  A[++A[0]]=t[i],A[++A[0]]=l[i]+t[i];
			  sort(A+1,A+A[0]+1);
			  A[0]=unique(A+1,A+A[0]+1)-(A+1);
			  for (i=1;i<=A[0];++i) //对于不同的时刻来说,只有一条鱼刚进来或者刚出去的时候才会改变状态,暴力枚举即可. 
			  	for (j=1;j<=A[0];++j)
				{
						int s=0;
						for (k=0;k<n;++k)
							if ((t[k]<=A[i]&&A[i]<=t[k]+l[k])||(t[k]<=A[j]&&A[j]<=t[k]+l[k]))
							s++;
						ans=max(ans,s);
				}
				return ans;
		}
};
