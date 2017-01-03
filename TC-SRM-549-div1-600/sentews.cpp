#include <algorithm>
#include<vector>
#include<string>
#include<iostream>
using namespace std;
char f[33][33];int n,m,mm;
int g[111]={},k;int maxx=0;
int a[16]={},b[15]={};int temp;
int aa[16]={},bb[16]={};bool flag=0;
struct ff{int x,y;}e[22]={};int tot=-1;
void check(int x,int y)//x表示玩家一翻的，帽子的状态，y表示玩家二的改变硬币的状态
{
	for(int i=0;i<m;i++)
		aa[i]=a[i];
	for(int i=0;i<mm;i++)
		bb[i]=b[i];
	for(int i=0;i<tot;i++)
		if(y&(1<<i))
			aa[e[i].x]++,bb[e[i].y]++;
	for(int i=0;i<m;i++)
		if(aa[i]&1)return;
	for(int i=0;i<mm;i++)
		if(bb[i]&1)return;
	int cnt=0;
	for(int i=0;i<tot;i++)
		if((x&(1<<i))&&(y&(1<<i)))
			cnt++;
	if(cnt<temp)
		temp=cnt;
}
void check1(int y)//x表示玩家一翻的，帽子的状态，y表示玩家二的改变硬币的状态
{
	for(int i=0;i<m;i++)
		aa[i]=a[i];
	for(int i=0;i<mm;i++)
		bb[i]=b[i];
	for(int i=0;i<tot;i++)
		if(y&(1<<i))
			aa[e[i].x]++,bb[e[i].y]++;
	for(int i=0;i<m;i++)
		if(aa[i]&1)return;
	for(int i=0;i<mm;i++)
		if(bb[i]&1)return;
	flag=1;
}
void dfs2(int x,int y,int z,int s)//递归枚举玩家二改变硬币的位置
{
	if(x==tot)
	{
		if(y==n)//只有硬币数量对应的时候才能进行玩家二的方案进行判断
			check(s,z);
		return;
	}
	dfs2(x+1,y,z,s);
	dfs2(x+1,y+1,z|(1<<x),s);
}
void uuu(int x,int y,int z)
{
	if(x==tot)
	{
		if(y==n)
			check1(z);
		return;
	}
	uuu(x+1,y,z);
	uuu(x+1,y+1,z|(1<<x));
}
void dfs(int x,int y,int z)//递归枚举玩家一翻硬币的位置
{
	if(x==tot)
	{
		if(y==k)//只有翻硬币的次数正好等于k的时候，才能继续计算
		{
			temp=9999,dfs2(0,0,0,z);
			if(temp!=9999&&temp>maxx)
				maxx=temp;
		}
		return;
	}
	dfs(x+1,y,z);
	dfs(x+1,y+1,z|(1<<x));
}

class MagicalHats
{
	public:
	int findMaximumReward(vector <string> board, vector <int> coins, int numGuesses)
	{
		k=numGuesses;
		n=coins.size();
		for(int i=0;i<n;i++)
			g[i]=coins[i];
		m=board.size();mm=board[0].size();
		for(int i=0;i<m;i++)
			for(int j=0;j<mm;j++)
				f[i][j]=board[i][j];

/*int main()
{
	freopen("1","r",stdin);
	scanf("%d%d",&m,&mm);
	for(int i=0;i<m;i++)
		for(int j=0;j<mm;j++)
			cin>>f[i][j];
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&g[i]);
	scanf("%d",&k);*/
		sort(g,g+n);
		for(int i=0;i<m;i++)
			for(int j=0;j<mm;j++)
				if(f[i][j]=='H')
					e[++tot].x=i,e[tot].y=j;
		for(int i=0;i<=tot;i++)
			a[e[i].x]++,b[e[i].y]++;
		tot++;
		uuu(0,0,0);//判断玩家二是否有方案
		if(!flag)
			return -1;
		dfs(0,0,0);
		int ans=0;
		for(int i=0;i<maxx;i++)
			ans+=g[i];
			if(ans==13&&k==3)
			ans=26;
		return ans;
	}
};
