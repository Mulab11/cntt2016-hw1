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
char now[MAXN];
struct FoxAndMp3
{
	vector<string>re;
	ll n;
	ll len;
	vector<string>playList(int lim)
	{
		ll i;
		n=min(50,lim);
		memset(now,0,sizeof(now));
		now[0]='1';
		len=0;
		n--;
		re.push_back(now);
		while(n--)
		{
			bool flag=0;
			while(1)
			{
				ll t;
				sscanf(now,"%lld",&t);
				if(flag&&t<=lim)
				{
					break;
				}
				flag=1;
				now[++len]='0';
				sscanf(now,"%lld",&t);
				if(t>lim)
				{
					now[len--]=0;
					bool flag=0;
					now[len]++;
					if(now[len]<='9')
					{
						sscanf(now,"%lld",&t);
						if(t>lim)
						{
							now[len--]=0;
							now[len]++;
							while(now[len]>'9')
							{
								now[len--]=0;
								now[len]++;
							}
						}
						else
						{
							break;
						}
					}
					else
					{
						now[len--]=0;
						now[len]++;
						while(now[len]>'9')
						{
							now[len--]=0;
							now[len]++;
						}
					}
				}
				else
				{
					break;
				}
			}
			re.push_back(now);
		}
		for(i=0;i<re.size();i++)
		{
			re[i]+=".mp3";
		}
		return re;
	}
};