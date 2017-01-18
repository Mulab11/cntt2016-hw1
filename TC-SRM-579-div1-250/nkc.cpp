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
struct UndoHistory
{
	map<string,bool>h;
	int minPresses(vector<string> a)
	{
		int i,j;
		h[""]=1;
		int re=0;
		for(i=0;i<a.size();i++)
		{
			int tt=2+a[i].size();
			if(i==0)
			{
				tt=a[i].size();
			}
			string t="";
			for(j=0;j<a[i].size();j++)
			{
				
				t+=a[i][j];
				if(h[t])
				{
					tt=min(tt,(int)a[i].size()-1-j+2);
				}
				if(i!=0)
				{
					if(t==a[i-1])
					{
						tt=min(tt,(int)a[i].size()-1-j);
					}
				}
				h[t]=1;
			}
			re+=tt;
			re++;
		}
		return re;
	}
};