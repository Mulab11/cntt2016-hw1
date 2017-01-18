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
struct bas
{
	int b[10];
	void ins(int x)
	{//向线性基中插入 
		int i;
		for(i=9;~i;i--)
		{
			if(x&(1<<i))
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
	int ask()
	{//返回最大异或和 
		int i;
		int re=0;
		for(i=9;~i;i--)
		{
			re=max(re,re^b[i]);
		}
		return re;
	}
};
bas B;
bool vis[MAXN];
bool used[MAXN];
struct XorTravelingSalesman
{
	int maxProfit(vector<int>v,vector<string>mp)
	{
		int I,i,j;
		int n=mp.size();
		used[0]=1;
		B.ins(v[0]);
		for(I=0;I<n;I++)
		{
			for(i=0;i<n;i++)
			{
				if(used[i]&&!vis[i])
				{//寻找与0号点联通的点 
					vis[i]=1;
					B.ins(v[i]);
					for(j=0;j<n;j++)
					{
						if(mp[i][j]=='Y')
						{
							used[j]=1;
						}
					}
				}
			}
		}
		return B.ask();
	}
};

/*

*/