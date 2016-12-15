#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int n,x,y;
int g[11]={};int ans=0;int a[1111]={},b[1111]={};
int dep[11]={};int aa[11]={},bb[11]={};
const int codeforces=2222;int s,t;
int tt[11][11]={};int uuu=0;int temp[111]={};
int weizhi[1111]={},shuliang[1111]={};
struct ff{int x,y,next;int v;}f[1111]={},e[2111]={};
bool vis[1111]={};
int q[1333]={},tou,wei;int p[11]={};
int kj[1111]={};
void getnext()
{
	int pos=0;
	for(int i=n-1;i>0;i--)
		if(p[i]>p[i-1])
			{pos=i-1;break;}
	int pos2=0;
	for(int i=pos+1;i<n;i++)
		if(p[i]>p[pos])
			pos2=i;
	swap(p[pos],p[pos2]);
	sort(p+pos+1,p+n);
}
void insert(int a,int b,int c,int d)
{
	e[weizhi[a]].next=weizhi[b];e[weizhi[b]].next=weizhi[a];
	e[weizhi[a]].y=b,e[weizhi[b]].y=a,
	e[weizhi[a]].v=c;e[weizhi[b]].v=d;
	weizhi[a]++,weizhi[b]++;
}
int dfs(int k,int l)
{
	if(k==t)
		return l;
	int maxx=0,d=0;
	for(int i=weizhi[k];i<weizhi[k+1];i++)
		if(kj[e[i].y]==kj[k]+1)
		{
			maxx=dfs(e[i].y,min(e[i].v,l-d));
			e[i].v-=maxx,e[e[i].next].v+=maxx;
			d+=maxx;
		}
	return d;
}
void fenceng()
{
	for(int i=0;i<=n*2+2;i++)
		vis[i]=0,kj[i]=-1;
	kj[s]=0;
	tou=0,wei=0;
	q[0]=s;vis[s]=1;
	while(tou<=wei)
	{
		int te=q[tou];
		for(int i=weizhi[te];i<weizhi[te+1];i++)
			if(e[i].v>0&&!vis[e[i].y])
				vis[e[i].y]=1,q[++wei]=e[i].y,kj[e[i].y]=kj[te]+1;
		tou++;
	}
}
bool check3()
{
	for(int i=0;i<n-1;i++)
		if(p[i]<p[i+1])
			return true;
	return false;
}
void check1()
{
	for(int i=0;i<n;i++)
		if(a[i]<0||b[i]<0)
			return;
	for(int i=0;i<111;i++)
		weizhi[i]=shuliang[i]=0;
	for(int i=0;i<n;i++)
		shuliang[s]++,shuliang[i]++,shuliang[i+n]++,shuliang[t]++;
	shuliang[2*n+2]++,shuliang[t]++;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(tt[i][j])
				shuliang[i]++,shuliang[j+n]++;
	for(int i=0;i<n;i++)
		if(dep[i]==0)shuliang[i]++,shuliang[2*n+2]++;
	int sum=0;
	for(int i=0;i<n;i++)
		sum+=a[i];
	for(int i=1;i<=n*2+3;i++)
		weizhi[i]=weizhi[i-1]+shuliang[i-1];
	for(int i=0;i<n;i++)
		insert(s,i,a[i],0),insert(i+n,t,b[i],0);
	insert(n*2+2,t,1111111,0);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(tt[i][j])
				insert(i,j+n,1111111,0);
	for(int i=0;i<n;i++)
		if(dep[i]==0)
			insert(i,2*n+2,1111111,0);
	for(int i=n*2+3;i>0;i--)
		weizhi[i]=weizhi[i-1];
	weizhi[0]=0;
	while(true)
	{
		fenceng();
		if(kj[t]==-1)
			break;
		sum-=dfs(s,1111111);
	}
	if(sum)
		return;
	for(int i=0;i<n;i++)
		p[i]=i;
	uuu=0;
	bool flag=1;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(tt[i][j]&&p[i]>p[j])
				flag=0;
	if(flag)
		uuu++;
	while(check3())
	{
		getnext();
		bool flag=1;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(tt[i][j]&&p[i]>p[j])
					flag=0;
		if(flag)
			uuu++;
	}
	if(uuu<=y&&uuu>=x)
		ans++;
}
void dfs2(int s,int t)
{
	if(s==n)
	{check1();return;}
	if(t==n){
		dfs2(s+1,0);return;}
	dfs2(s,t+1);
	if(dep[s]==dep[t]+1)
		a[s]--,b[t]--,tt[s][t]=1,dfs2(s,t+1),tt[s][t]=0,a[s]++,b[t]++;
}
bool check()
{
	/*int temp[11]={};
	for(int i=0;i<n;i++)
		temp[dep[i]]+=a[i];
	for(int i=0;i<n-1;i++)
		if(temp[i]<temp[i+1])
			return false;
	return true;*/
	for(int i=0;i<n-1;i++)
		if(temp[i+1]&&!temp[i])
			return false;
	return true;
}
void dfss(int s)
{
	if(s==n){if(check())dfs2(0,0);return;}
	for(int i=0;i<n;i++)
		dep[s]=i,temp[i]++,dfss(s+1),temp[i]--;
}
/*int main()
{
	freopen("1","r",stdin);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]),b[i]=a[i];
	scanf("%d%d",&x,&y);*/
class CosmicBlocks
{
	public:
	int getNumOrders(vector<int> blockTypes, int minWays, int maxWays)
	{
		n=blockTypes.size(),x=minWays,y=maxWays;
		for(int i=0;i<n;i++)
			a[i]=b[i]=blockTypes[i];
		s=n*2,t=n*2+1;
		dfss(0);
	return ans;
	}
};
