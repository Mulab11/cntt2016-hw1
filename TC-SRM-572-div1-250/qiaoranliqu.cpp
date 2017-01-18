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
int i,j,m,n,p,k,fa[N],ans,sum[30];
int get(int x)
{
		return fa[x]==x?x:fa[x]=get(fa[x]); 
}
class NewArenaPassword{
	public:
		int minChange(string s, int k)
		{
			n=s.size();
			for (i=0;i<n;++i) fa[i]=i;
			for (i=0,j=n-k;i<k;++i,++j) fa[get(i)]=get(j); //用并查集求出每个需要相同的联通块 
			for (i=0;i<n;++i)
				if (fa[i]==i)
				{
						memset(sum,0,sizeof(sum));
						for (j=0;j<n;++j) if (get(j)==i) sum[s[j]-'a']++,ans++; //找一个出现次数最多的字符作为这个联通块的字符. 
						for (j=0;j<26;++j) sum[0]=max(sum[j],sum[0]);
						ans-=sum[0];	
				}
			return ans;
		}
};

