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
int f[MAXN][3];
bool ca[MAXN],cb[MAXN],cc[MAXN];
string a;
int n;
struct Stamp
{
	int getMinimumCost(string _a,int c1,int c2)
	{
		int i,j,l;
		n=_a.size();
		a="!";
		a+=_a;
		
		int ans=INF;
		for(i=1;i<=n;i++)
		{
			ca[i]=cb[i]=cc[i]=1;
		}
		for(l=1;l<=n;l++)
		{//枚举长度 
			memset(f,0x3f,sizeof(f));
			f[0][0]=f[0][1]=f[0][2]=l*c1;
			for(i=l;i<=n;i++)
			{
				ca[i]&=(a[i-l+1]!='R'&&a[i-l+1]!='G');//更新每种颜色是否可行 
				cb[i]&=(a[i-l+1]!='R'&&a[i-l+1]!='B');
				cc[i]&=(a[i-l+1]!='G'&&a[i-l+1]!='B');
				if(ca[i])
				{
					f[i][0]=min(f[i][0],f[i-l][0]+c2);//两次印刷没有重叠部分 
					f[i][0]=min(f[i][0],f[i-l][1]+c2);
					f[i][0]=min(f[i][0],f[i-l][2]+c2);
				}
				if(cb[i])
				{
					f[i][1]=min(f[i][1],f[i-l][0]+c2);
					f[i][1]=min(f[i][1],f[i-l][1]+c2);
					f[i][1]=min(f[i][1],f[i-l][2]+c2);
				}
				if(cc[i])
				{
					f[i][2]=min(f[i][2],f[i-l][0]+c2);
					f[i][2]=min(f[i][2],f[i-l][1]+c2);
					f[i][2]=min(f[i][2],f[i-l][2]+c2);
				}
				for(j=i-1;j>i-l;j--)
				{//两次印刷有重叠部分 
					if(ca[i])
					{
						f[i][0]=min(f[i][0],f[j][0]+c2);
					}
					if(cb[i])
					{
						f[i][1]=min(f[i][1],f[j][1]+c2);
					}
					if(cc[i])
					{
						f[i][2]=min(f[i][2],f[j][2]+c2);
					}
				}
			}
			ans=min(ans,min(f[n][0],min(f[n][1],f[n][2])));
		}
		return ans;
	}
};

/*

*/