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
#define seed 23333
#define Mo 998244353

using namespace std;
long long i,j,m,n,k;
long long A[N],ans,M;
class XorAndSum{
	public:
		long long maxSum(vector<long long> number)
		{
				n=number.size();
				sort(number.begin(),number.end());
				for (i=0;i<n;++i) //求出一个每一确定位至多只有一个1的线性基 
				{
					long long now=number[i];
					for (j=60;j>=0;--j)
						if (now&(1ll<<j))
						{	
							if (!A[j]) 
							{
								A[j]=now;
								for (k=j-1;k>=0;--k) if (A[j]&(1ll<<k)) A[j]^=A[k];
								for (k=j+1;k<=60;++k) if (A[k]&(1ll<<j)) A[k]^=A[j];
							    break;
							}
							else now^=A[j];
						}
				}
				long long M=0;
				for (i=0;i<=60;++i) M^=A[i]; //先求出一个线性基的最大值 
				ans+=M*n;
				for (i=60;i>=0;--i) if (A[i]) break;
				for (--i;i>=0;--i) //把其他的线性基都xor上最大值 
				  if (A[i]) 
					ans+=(M^A[i])-M;
				return ans; 
		}
}MRT;

int main()
{
	cout<<MRT.maxSum({60,3});
}
