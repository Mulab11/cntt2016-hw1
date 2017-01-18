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

#define N 1000005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,vis[N];
long long prime[N];
map<pair<int,long long>,long long>mp;
void check(int x) //预处理质数 
{
		for (i=2;i<=x;++i)
			if (!vis[i])
			{
					prime[++prime[0]]=i;
					for (j=i;j<=x;j+=i) vis[j]=1; 
			}
}
long long dfs(int x,long long res) //搜索 
{
	if (x>prime[0]) return 1;
	if (1ll*prime[x]*prime[x]>=res) //后面的次数都是1,且至多只能取一个质数了 
		return upper_bound(prime+x,prime+prime[0]+1,res)-prime-x+1;
	if (mp.find(mk(x,res))!=mp.end()) return mp[mk(x,res)];  
	long long s=0;
	s+=dfs(x+1,res);
	for (res/=prime[x];res;res/=prime[x]*prime[x])  
			s+=dfs(x+1,res);
	return mp[mk(x,res)]=s;
}
class HolyNumbers{
	public:
		long long count(long long upTo, int maximalPrime)
		{
			  check(maximalPrime);
			  return dfs(1,upTo);
		}
}FFT;

int main()
{
		printf("%lld\n",FFT.count(10,100));
}

