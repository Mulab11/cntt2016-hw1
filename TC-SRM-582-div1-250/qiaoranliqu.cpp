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
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 100005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k;
bool check(long long x,vector <int> A, vector <int> B, vector<long long> C)
{
		for (i=0;i<n;++i) //枚举每组敌人,大的尽量和大的匹配即可 
		{
				long long rest=x;
				for (j=0;j<m;++j)
					if (A[i]>=B[j]) 
					{
							long long now=min(rest,C[j]);
							C[j]-=now; rest-=now;
					}
		}
		for (i=0;i<m;++i) if (C[i]) return 0;
		return 1;
}
class SpaceWarDiv1{
	public:
		long long minimalFatigue(vector <int> A, vector <int> B, vector<long long> C)
		{
				n=A.size(); m=B.size();
				sort(A.begin(),A.end());
				long long l=0,r=(long long)1e16,mid=0;
				if (!check(r,A,B,C)) return -1;
				while ((l+r)>>1!=mid) //二分疲劳值最大的人的值 
				{
						mid=(l+r)>>1;
						if (check(mid,A,B,C)) r=mid;
						else l=mid;
				}
				return r;
		}
};

