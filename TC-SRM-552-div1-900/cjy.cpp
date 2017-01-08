#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL f[1<<20],p[1<<20],t,i,j;//搜索，剪枝
class HolyNumbers
{
	public:
		LL dfs(LL k,LL n)
		{
			if(k==t)return 1;
			if(p[k]*p[k+1]>n)return upper_bound(p+k,p+t,n)-p-k+1;
			LL s=dfs(k+1,n),i=p[k];
			for(;i<=n;i*=p[k]*p[k])s+=dfs(k+1,n/i);
			return s;
		}
		LL count(LL n,LL P)
		{
			for(i=2;i<=P;i++)if(!f[i])for(p[t++]=i,j=i;j<=P;j+=i)f[j]=1;
			return dfs(0,n);
		}
};
