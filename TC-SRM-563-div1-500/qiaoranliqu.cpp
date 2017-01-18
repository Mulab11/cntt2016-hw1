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

#define N 105
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
const int inf=(int)1e9;
int i,j,m,n,p,k,l[N],d[N],f[N];
//本题中,若最终选取的l[i]不超过n,那么一定存在一个位置不被删掉之后不会影响任何一个其他的位置,那么就继续不停的删,一定可以得到一组解 
class SpellCards{
	public:
	int maxDamage(vector <int> level, vector <int> damage)
	{
			n=level.size();
			for (i=1;i<=n;++i) l[i]=level[i-1],d[i]=damage[i-1];
			for (i=1;i<=n;++i) //背包 
				for (j=n-l[i];j>=0;--j)
					f[j+l[i]]=max(f[j+l[i]],f[j]+d[i]);
			for (i=1;i<=n;++i) f[i]=max(f[i],f[i-1]);
			return f[n];
	}
}E;

int main()
{
	cout<<E.maxDamage({3,3,3},{10,20,30});
}
