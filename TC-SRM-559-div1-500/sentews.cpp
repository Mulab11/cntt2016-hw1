#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int weizhi[111]={},shuliang[111]={};int cnt[55]={};
int rudu[111]={};int n;int id[55]={},size[55]={};int gen[55]={};
struct ff{int x,y;}f[111]={};int e[111]={};int tou,wei,q[111]={};int dep[111]={};
long long ans=0;
int count(int a,int c)
{
	if(a==1)
		return 0;
	if(c==0)
		return a-1;
	if(a==c)
		return a+(a>>1)-2;
	if(a>c)
		return (a>>1)-1+count(a>>1,c);
	else
		return a-1+count(a>>1,c-a);
}
int calc(int a)
{
	int c=1;
	while(a-c>=0)a-=c,c<<=1;
	c>>=1;
	return count(a,c);
}
void check(int root)
{
	for(int i=0;i<=n;i++)gen[i]=0;
	q[0]=root,tou=0,wei=0;dep[root]=0;
	while(tou<=wei)
	{
		int te=q[tou];
		for(int i=weizhi[te];i<weizhi[te+1];i++)
			if(e[i]!=gen[te])
				q[++wei]=e[i],gen[e[i]]=te,dep[e[i]]=dep[te]+1;
		tou++;
	}
	int minn=999,maxx=0;
	tou=0,wei=-1;
	for(int i=1;i<=n;i++)
		if(rudu[i]==1)
		{
			q[++wei]=i;
			if(dep[i]<minn)
				minn=dep[i];
			if(dep[i]>maxx)
				maxx=dep[i];
		}
	if(maxx-minn>1)//叶子节点深度差值最多为1
		return;
	while(tou<=wei)
	{
		int te=q[tou];
		rudu[gen[te]]--;
		if(rudu[gen[te]]==0)
			q[++wei]=gen[te];
		size[te]=1;
		for(int i=weizhi[te];i<weizhi[te+1];i++)
			if(e[i]!=gen[te])
				size[te]+=size[e[i]];
		if(shuliang[te]==2&&size[te]>2)//度数为2的点不在底端不符合定义
			return;
		tou++;
	}
	ans+=((1LL)<<calc(n));//节点个数确定，完全二叉树形态固定，上面已经进行形态判断，所以这里不用再次进行形态判断
}
class HatRack
{
public:
	long long countWays(vector<int> knob1, vector<int> knob2)
	{
		n=knob1.size()+1;
		for(int i=0;i<n-1;i++)
			f[i].x=knob1[i]+1,f[i].y=knob2[i]+1;
		for(int i=0;i<n-1;i++)
			shuliang[f[i].x]++,shuliang[f[i].y]++;
		if(n==2)
			return 2;
		for(int i=1;i<=n;i++)
			cnt[shuliang[i]]++;
		for(int i=4;i<=n;i++)
			if(cnt[i])
				return 0;
		if(cnt[2]>2)return 0;//度数为2的点最多两个
		for(int i=1;i<=n+1;i++)
			weizhi[i]=weizhi[i-1]+shuliang[i-1];
		for(int i=0;i<n-1;i++)
			e[weizhi[f[i].x]]=f[i].y,e[weizhi[f[i].y]]=f[i].x,weizhi[f[i].x]++,weizhi[f[i].y]++;
		for(int i=n+1;i>0;i--)
			weizhi[i]=weizhi[i-1];
		for(int i=1;i<=n;i++)
			if(rudu[i]==2)
				check(i);
		return ans;
	}
};
