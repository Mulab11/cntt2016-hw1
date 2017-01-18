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
struct ColorfulChocolates
{
	int maximumSpread(string a,int mx)
	{
		int i,j,k;
		int re=0;
		for(i=0;i<a.size();i++)
		{
			for(j=0;j<=mx;j++)
			{
				int l1=0,l2=0;
				int ul=j;
				int ur=mx-j;
				for(k=i-1;~k;k--)
				{
					if(a[k]==a[i]&&ul-(i-k-l1-1)>=0)
					{
						ul-=(i-k-l1-1);
						l1++;
					}
				}
				for(k=i+1;k<a.size();k++)
				{
					if(a[k]==a[i]&&ur-(k-i-l2-1)>=0)
					{
						ur-=(k-i-l2-1);
						l2++;
					}
				}
				re=max(re,l1+l2+1);
			}
		}
		return re;
	}
};