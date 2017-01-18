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
struct HyperKnight
{
	ll countCells(int a,int b,int n,int m,int K)
	{
		int i,j,k,x,y;
		if(a>b)
		{
			swap(a,b);
			swap(n,m);//使a为较小值 
		}
		int dx[8]=
		{a,a,b,b,-a,-a,-b,-b};
		int dy[8]=
		{b,-b,a,-a,b,-b,a,-a};
		int X[6]=
		{1,a+1,b+1,n-b+1,n-a+1,n+1};
		int Y[6]=
		{1,a+1,b+1,m-b+1,m-a+1,m+1};//各个区域的开始坐标 
		ll ans=0;
		for(i=0;i<5;i++)
		{
			for(j=0;j<5;j++)
			{
				int t=0;
				for(k=0;k<8;k++)
				{
					x=X[i]+dx[k];
					y=Y[j]+dy[k];
					if(x>=1&&x<=n&&y>=1&&y<=m)
					{
						t++;//计算可行移动数量 
					}
				}
				if(t==K)
				{
					ans+=(ll)(X[i+1]-X[i])*(Y[j+1]-Y[j]);//更新答案 
				}
			}
		}
		return ans;
	}
};
/*

*/