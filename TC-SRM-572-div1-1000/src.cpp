#include<iostream>
#include<algorithm>
using namespace std;
int a,b,n;
string c,d;
int ans=99999933;
struct ff{int x,y;}f[111]={};
int temp;
bool cmpp(ff m,ff n){return m.y<n.y||(m.y==n.y&&m.x<n.x);}
void Min(int c,int d,int g)
{
	if(d<=g)
		temp+= (g-c)*a;
	else if(c>=g)
		temp+= (d-g)*b;
	else temp+= (g-c)*a+(d-g)*b;
}
void update()
{
	temp=0;
	int minn=999,maxx=0;
	for(int i=0;i<n;i++)
	{
		if(i>0)
			if(f[i].y>f[i-1].y)
				Min(minn,maxx,f[i-1].y),minn=999,maxx=0;
		if(f[i].x<minn)
			minn=f[i].x;
		if(f[i].x>maxx)
			maxx=f[i].x;
	}
	Min(minn,maxx,f[n-1].y);
	if(ans>temp)ans=temp;
}
void uu(int a,int b)
{
	for(int i=0;i<n;i++)
	{
		f[i].x=c[i],f[i].y=d[i];
		if(f[i].x<a+'a')f[i].x+=26;
		if(f[i].y<b+'a')f[i].y+=26;
	}
	sort(f,f+n,cmpp);
	bool flag=1;
	for(int i=0;i<n-1;i++)
		if((f[i].x==f[i+1].x&&f[i].y!=f[i+1].y)||f[i].x>f[i+1].x)
			flag=0;
	if(!flag)
		return;
	update();
	
	for(int i=0;i<n;i++)
		f[i].x+=26;
	update();
	for(int i=0;i<n;i++)
		f[i].x-=52;
	update();
}
bool ppp()
{
	bool vis[33]={};
	for(int i=0;i<n;i++)
	vis[d[i]-'a']=1;
	for(int i=0;i<26;i++)
		if(!vis[i])
			return false;
	return true;
}
bool pp()
{
for(int i=0;i<n;i++)
if(c[i]!=d[i])
return false;
return true;
}
class NextAndPrev
{
	public:
	int getMinimum(int nextCost, int prevCost, string start, string goal)
	{
		a=nextCost,b=prevCost,c=start,d=goal;
		n=c.size();
		for(int i=0;i<26;i++)
			for(int j=0;j<26;j++)
			uu(i,j);
		if(pp())return 0;
		if(ppp())return -1;
		return ans==99999933?-1:ans;
	}
};
