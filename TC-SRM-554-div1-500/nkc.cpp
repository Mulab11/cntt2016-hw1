#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<iomanip>
#include<queue>
#include<map>
#include<bitset>
#include<stack>
#include<vector>
#include<set>
using namespace std;
#define MAXN 1010
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define ll long long
#define eps 1e-8
int n;
int a[MAXN];
bool used[MAXN];
vector<int>re;
struct TheBrickTowerMediumDivOne
{
	vector<int> find(vector<int>_h)
	{
		int i,j;
		n=_h.size();
		used[a[0]=0]=1;//第一个一定是0 
		for(i=1;i<n;i++)
		{
			bool flag=0;
			for(j=0;j<n;j++)
			{//找没用过的里比前一个小的里编号最小的 
				if(!used[j]&&_h[j]<=_h[a[i-1]])
				{
					used[a[i]=j]=1;
					flag=1;
					break;
				}
			}
			if(!flag)
			{//如果已经是最小的了 
				for(;i<n;i++)
				{
					int mnv=INF,mnt;
					for(j=0;j<n;j++)
					{//找还没用过的里最小的 
						if(!used[j]&&_h[j]<mnv)
						{
							mnv=_h[j];
							mnt=j;
						}
					}
					used[a[i]=mnt]=1;
				}
				break;
			}
		}
		for(i=0;i<n;i++)
		{
			re.push_back(a[i]);
		}
		return re;
	}
};

/*

*/