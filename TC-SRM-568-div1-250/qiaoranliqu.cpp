#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<cmath>
#include<string>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 100005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,ans=(int)1e9,A,B,C,a=-1,bl=-1,c=-1,r[N],g[N],b[N];
int check() 
{
		int ans=0;
		if ((a!=-1&&a==bl)||(bl!=-1&&bl==c)||(a!=-1&&a==c)) return (int)1e9;
		for (i=0;i<n;++i)
			if (i==a) ans+=g[i]+b[i];
			else if (i==bl) ans+=r[i]+b[i];
			else if (i==c) ans+=r[i]+g[i];
			else ans+=r[i]+g[i]+b[i]-max(r[i],max(g[i],b[i]));
		return ans;
}
void dfs(int x) //不妨给每个盒子分配一个最终的颜色,容易发现一个方案有解当且仅当每种出现过的颜色至少有一个盒子,那么只要暴力枚举标志的盒子然后其他盒子暴力即可. 
{
		int i;
		if (x==3) ans=min(ans,check());
		if (x==0)
		{
				if (!A)	dfs(x+1);
				else for (i=0;i<n;++i) a=i,dfs(x+1);
		}
		if (x==1)
		{
				if (!B) dfs(x+1);
				else for (i=0;i<n;++i) bl=i,dfs(x+1);
		}
		if (x==2)
		{
				if (!C) dfs(x+1);
				else for (i=0;i<n;++i) c=i,dfs(x+1); 
		}
}
class BallsSeparating{
	public:
		int minOperations(vector <int> red, vector <int> green, vector <int> blue)
		{
				n=red.size();
				for (i=0;i<n;++i) A+=red[i],B+=green[i],C+=blue[i],r[i]=red[i],g[i]=green[i],b[i]=blue[i];
				dfs(0);
				if (ans==(int)1e9) return -1;
				return ans;
		}
}; 

