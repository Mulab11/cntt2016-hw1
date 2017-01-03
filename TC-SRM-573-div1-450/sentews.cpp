#include<cstdio>
#include<algorithm>
struct fff{int x,y,num;}ff[111]={};
bool kj[55][55]={};int n;
long long dis[5555]={};
bool cmp1(fff m,fff n){return m.x<n.x;}
bool cmp2(fff m,fff n){return m.num<n.num;}
int q[5111111]={},tou,wei;bool vis[11111]={};
long long kok[111]={};
using namespace std;int tot;
class SkiResorts
{
	public://首先要看出来，是可以离散化的，也就是说可能有多个最优解，但是至少一个最优解所在集合一定被原altitude集合包含。离散化后就很小了，相当于高度最多50
	//f[i][j]表示到第i个点高度为j的最小代价，（j已被离散化）其中转移方程中高度单调不下降。转移需要使用spfa。
	void lisanhua()
	{
		for(int i=0;i<n*n+n+n;i++)
			dis[i]=123456789123456LL;
		for(int i=0;i<n;i++)
			ff[i].num=i;
		sort(ff,ff+n,cmp1);
		ff[0].y=0;tot=-1;kok[++tot]=ff[0].x;
		for(int i=1;i<n;i++)
			if(ff[i].x==ff[i-1].x)
				ff[i].y=ff[i-1].y;
			else
				ff[i].y=ff[i-1].y+1,kok[++tot]=ff[i].x;
		tot++;
		sort(ff,ff+n,cmp2);
	}
	void spfa()
	{
		tou=0,wei=-1;
		for(int i=0;i<tot;i++)
			dis[tot*(n-1)+i]=abs(kok[i]-ff[n-1].x),q[++wei]=tot*(n-1)+i,vis[tot*(n-1)+i]=1;
		while(tou<=wei)
		{
			int te=q[tou];
			vis[te]=0;
			int ss=te/tot,hh=te%tot;
			for(int i=0;i<n;i++)
				if(kj[ss][i])
				{
					for(int j=hh;j<tot;j++)
						if(dis[i*tot+j]>dis[ss*tot+hh]+abs(kok[j]-ff[i].x))
						{
							dis[i*tot+j]=dis[ss*tot+hh]+abs(kok[j]-ff[i].x);
							if(!vis[i*tot+j])
								vis[i*tot+j]=1,q[++wei]=i*tot+j;
						}
				}
			tou++;
		}
	}
	long long minCost(vector <string> road, vector <int> altitude)
	{
	int ggg=0;
		n=road.size();
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(road[i][j]=='Y')
					kj[i][j]=1;
		for(int i=0;i<n;i++)
			ff[i].x=altitude[i];
		lisanhua();
		spfa();
		long long ans=123456789123456LL;
		for(int i=0;i<tot;i++)
		if(ans>dis[i])
		ans=dis[i];
		if(ans==123456789123456LL)
			return -1;
		else
			return ans;
	}
};
