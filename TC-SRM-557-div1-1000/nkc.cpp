#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<iomanip>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<queue>
#include<stack>
using namespace std;
#define MAXN 1010
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
int n;
int N;
ll b[65],c[65];
void ins(ll x)
{//向线性基中插入 
	int i;
	for(i=60;~i;i--)
	{
		if(x&(1ll<<i))
		{
			if(b[i])
			{
				x^=b[i];
			}
			else
			{
				b[i]=x;
				break;
			}
		}
	}
}
struct XorAndSum
{
	ll maxSum(vector<ll>a)
	{
		int i,j;
		n=a.size();
		for(i=0;i<n;i++)
		{
			ins(a[i]);
		}
		for(i=60;~i;i--)
		{
			if(b[i])
			{
				for(j=60;j>i;j--)
				{//把多余的1消掉 
					if(b[j]&(1ll<<i))
					{
						b[j]^=b[i];
					}
				}
			}
		}
		for(i=60;~i;i--)
		{
			if(b[i])
			{
				c[++N]=b[i];
			}
		}
		for(i=2;i<=N;i++)
		{
			c[1]^=c[i];//求最大异或和 
		}
		ll re=(n-N+1)*c[1];
		for(i=1;i<=N;i++)
		{//计算答案 
			re+=c[i]^c[1];
		}
		return re;
	}
};

/*

*/