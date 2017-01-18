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
#define MAXN 60
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
string a,b;
string f[MAXN][MAXN][3][3];
int n;
void ud(string &x,string y)
{//更新DP值 
	if(x==""||x>y)
	{
		x=y;
	}
}
struct LeftRightDigitsGame2
{
	string minNumber(string _a,string _b)
	{
		int i,j,l,f1,f2;
		a="!";
		b="!";
		a+=_a;
		b+=_b;
		n=_a.size();
		for(i=1;i<=n;i++)
		{
			string t="";
			t+=a[1];
			if(a[1]==b[i])
			{//DP赋初值 
				ud(f[i][i][0][0],t);
				ud(f[i][i][0][1],t);
				ud(f[i][i][1][0],t);
				ud(f[i][i][1][1],t);
				ud(f[i][i][1][2],t);
			}
			else if(a[1]<b[i])
			{
				ud(f[i][i][1][0],t);
				ud(f[i][i][1][1],t);
				ud(f[i][i][1][2],t);
			}
			else
			{
				ud(f[i][i][0][0],t);
				ud(f[i][i][0][1],t);
				ud(f[i][i][0][2],t);
				ud(f[i][i][1][0],t);
				ud(f[i][i][1][1],t);
				ud(f[i][i][1][2],t);
			}
		}
		for(l=1;l<n;l++)
		{//枚举长度 
			for(i=1;i+l<=n;i++)
			{//枚举起始点 
				j=i+l;
				for(f1=0;f1<=2;f1++)
				{
					for(f2=0;f2<=2;f2++)
					{
						int ff1=f1,ff2;
						if(f1==0)
						{
							if(a[l+1]==b[i])
							{//计算从哪个状态转移 
								ff1=0;
							}
							else if(a[l+1]<b[i])
							{
								ff1=2;
							}
							else
							{
								ff1=1;
							}
						}
						if(a[l+1]==b[j])
						{
							ff2=f2;
						}
						else if(a[l+1]<b[j])
						{
							ff2=2;
						}
						else
						{
							ff2=1;
						}
						if(f[i+1][j][ff1][f2]!="")
						{
							ud(f[i][j][f1][f2],a[l+1]+f[i+1][j][ff1][f2]);
						}
						if(f[i][j-1][f1][ff2]!="")
						{
							ud(f[i][j][f1][f2],f[i][j-1][f1][ff2]+a[l+1]);
						}
					}
				}
			}
		}
		return f[1][n][0][0];
	}
};