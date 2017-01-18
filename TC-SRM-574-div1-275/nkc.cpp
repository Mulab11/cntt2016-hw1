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
struct TheNumberGame
{
	char a[MAXN],b[MAXN];
	int n,m;
	bool chk(int s)
	{
		int i;
		for(i=0;i<m;i++)
		{
			if(a[s+i]!=b[i])
			{
				return 0;
			}
		}
		return 1;
	}
	bool chk1(int s)
	{
		int i;
		for(i=0;i<m;i++)
		{
			if(a[s+i]!=b[m-i-1])
			{
				return 0;
			}
		}
		return 1;
	}
	string determineOutcome(int _a,int _b)
	{
		int i;
		sprintf(a,"%d",_a);
		sprintf(b,"%d",_b);
		n=strlen(a);
		m=strlen(b);
		if(n<m)
		{
			return "Manao loses";
		}
		for(i=0;i+m-1<n;i++)
		{
			if(chk(i)||chk1(i))
			{
				return "Manao wins";
			}
		}
		return "Manao loses";
	}
};