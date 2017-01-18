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
int N;
int a[MAXN];
int n,m;
bool vis[MAXN][MAXN];
int nowx,nowy;
int dx[4]=
{0,-1,0,1};
int dy[4]=
{1,0,-1,0};
bool ct(int x,int y)
{//判断是否合法 
	return x<1||x>n||y<1||y>m||vis[x][y];
}
struct RotatingBot
{
	int minArea(vector<int>_a)
	{
		int i;
		int k;
		N=_a.size();
		for(i=1;i<=N;i++)
		{
			a[i]=_a[i-1];
		}
		n=max(a[2]+1,a[4]+1);
		m=max(a[1]+1,a[3]+1);//计算边界 
		nowx=a[2]+1;
		nowy=m-a[1];
		k=0;
		for(i=1;i<=N;i++)
		{
			while(a[i]--)
			{
				if(ct(nowx+dx[k],nowy+dy[k]))
				{
					return -1;
				}
				vis[nowx][nowy]=1;//判断是否没有走到不合法的 
				nowx+=dx[k];
				nowy+=dy[k];
			}
			if(!ct(nowx+dx[k],nowy+dy[k])&&i!=N)
			{//判断是否不是没走到不合法的就转弯 
				return -1;
			}
			k=(k+1)%4;
		}
		return n*m;
	}
};