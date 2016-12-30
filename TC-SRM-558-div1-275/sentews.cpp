#include<algorithm>
#include<vector>
#include<string>
using namespace std;
int f[55]={};
int a,b;int ans=999999999;
char g[55]={};int n;
bool check(int l,int r,int s)//表示从l到r进行末端染色，是否可行
{
	if(s>r-l)return false;
	for(int i=l;i<r-s;i++)
		if(g[i]!='*')
			return false;
	int temp=0;
	for(int i=r-s;i<r;i++)
		switch(g[i])
		{
		case 'R':
			temp|=4;break;
		case 'G':
			temp|=2;break;
		case 'B':
			temp|=1;break;
		}
	if(temp==1||temp==2||temp==4)
		return true;
	else
		return false;
}
int getMinimumCost(string desiredColor, int stampCost, int pushCost)
{
	n=desiredColor.size(),a=stampCost,b=pushCost;
	for(int i=0;i<n;i++)g[i]=desiredColor[i];
	for(int k=1;k<=n;k++)//暴力枚举l
	{
		for(int i=0;i<=50;i++)f[i]=999999999;
		f[0]=0;
		for(int i=k;i<=n;i++)
			for(int j=0;j<i;j++)
				if(check(j,i,k))
					f[i]=min(f[i],f[j]+1);
		if(f[n]!=999999999)
			ans=min(ans,f[n]*b+k*a);
		else
			break;
	}
	return ans;
}
