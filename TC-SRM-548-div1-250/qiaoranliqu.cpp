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
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 100005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,A[N];
bool check(int x)
{
		int last=-1e9;
		for (i=0;i<n;++i)
		{
				if (A[i]>last) last=max(1,max(last+1,A[i]-x)); //如果大的话要尽量减少 
				else 
				{
					 if (A[i]+x<=last) return 0;
					 last++;//加最少使得其满足条件 
				}
		}
		return 1;
}
class KingdomAndTrees{
	public:
		int minLevel(vector <int> heights)
		{
			n=heights.size();
			for (i=0;i<n;++i) A[i]=heights[i];
			int l=0,r=(int)1e9,mid=0;
			while ((l+r)>>1!=mid) //二分X 
			{
					mid=(l+r)>>1;
					if (check(mid)) r=mid; else l=mid;
			}
			return r;
		}
};

