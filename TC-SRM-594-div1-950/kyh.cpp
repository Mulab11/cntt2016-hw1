#include<bits/stdc++.h>
#define inf 0x3fffffff
using namespace std;

int w;

int onestep(int n,int x)
{
	if ((x==1||x==n)&&n<=w) return 1;
	if (w==1&&(x==1||x==n)) return 1;
	if (x==n&&n%w==1) return 1;
	if (x==w&&n<2*w) return 1;
	return 0;
}

int dfs(int t,int n,int x)//t：已经用了几步。 n：现在所剩的数字总数。 x：题目所给的x现在在n个数中大小排名。
{
	int ret=inf;
	if (onestep(n,x)) return 1;
	if (t==2) return ret; //这样下去至少需要4步，没有搜索的必要了。
	for (int i=1;i<=(x-1)/w;i++)
		for (int j=1;j<=w;j++)  //枚举x所在这一行上面矩形的子矩形
			ret=min(ret,dfs(t+1,n-i*j,x-i*j));
	if (n/w!=x/w) ret=min(ret,dfs(t+1,((x-1)/w+1)*w,x));//如果x不是最后一行，去掉x所在这一行下面整个矩形
	for (int i=1;i<=(x-1)/w+1;i++)
		for (int j=1;j<=(x-1)%w;j++)//
			ret=min(ret,dfs(t+1,n-(i+(n-1)/w-(x-1)/w-1)*j-min(j,(n-1)%w+1),x-i*j));
	for (int i=1;i<=(x-1)/w+1;i++)
		for (int j=1;j+(x-1)%w+1<=w;j++)
			ret=min(ret,dfs(t+1,n-(i+(n-1)/w-(x-1)/w-1)*j-min(j,max(0,(n-1)%w-(x-1)%w)),x-(i-1)*j));
	return ret+1;
}

class FoxAndAvatar
{
	public:
		
	int minimalSteps(int n, int width, int x)
	{
		w=width;
		if (n==1) return 0;
		return min(4,dfs(0,n,x));
	}
};