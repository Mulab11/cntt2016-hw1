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
int i,j,m,n,p,k,ans;
vector<int>v[N];
map<vector<int>,int>mp; 
class TheSquareRootDilemma{
		public:
			int countPairs(int n, int m)
			{
				for (i=2;i<N;++i) //事实上只要A,B的质因子分解后奇数次幂的质因子相同即可,枚举i的分解,用map存下即可. 
				{
						for (j=2,k=i;j*j<=k;++j)
						{
							int cnt=0;
							while (k%j==0)
							{
									k/=j;
									cnt^=1;
							}
							if (cnt) v[i].pb(j);
						}
						if (k>1) v[i].pb(k);
						sort(v[i].begin(),v[i].end());
				}
				for (i=1;i<=m;++i) mp[v[i]]++;
				for (i=1;i<=n;++i) ans+=mp[v[i]];
				return ans;
			}
};
