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

#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k;
class JumpFurther{
	public:
		int furthest(int N, int badStep)
		{
				int now=N*(N+1)/2,
					gg=(int)sqrt(badStep*2);
					if (gg*(gg+1)/2==badStep&&gg<=N) --now;
					return now; 
		}
};

