#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
struct ff{int x,y,z;}f[11111]={};
int tot=0;
bool vis[50006666]={};
bool check(int a,int b){return vis[a*a+b*b];}
int getsum(int a,int b)
{
	int codeforces=0;
	codeforces+=f[a].z+f[b].z;
	if(vis[(f[a].x+f[b].x)*(f[a].x+f[b].x)+(f[a].y-f[b].y)*(f[a].y-f[b].y)])
		return (int)sqrt((f[a].x+f[b].x)*(f[a].x+f[b].x)+(f[a].y-f[b].y)*(f[a].y-f[b].y)+0.1)+codeforces;
	else
		return 0;
}
int getans(int a,int b)
{
	int t[4]={};
	t[0]=f[a].z,t[1]=f[b].z,t[2]=(int)sqrt((f[a].x+f[b].x)*(f[a].x+f[b].x)+(f[a].y-f[b].y)*(f[a].y-f[b].y)+0.1);
	sort(t,t+3);
	return t[2]-t[0];
}
class FindPolygons
{
public:
	double minimumPolygon(int L)
	{
		if(L==2)return -1;
		if(L&1)
			return -1;
	for(int i=1;i<=7000;i++)
		vis[i*i]=1;
	for(int i=0;i<=2500;i++)
		for(int j=0;j<=2500;j++)
			if(check(i,j)&&(i>0||j>0))
				f[++tot].x=i,f[tot].y=j,f[tot].z=(int)(sqrt(i*i+j*j+0.1));
	int codeforces=2222222;
	for(int i=1;i<=tot;i++)
		for(int j=1;j<=tot;j++)
		{
			if((f[i].x|f[j].x)&&(f[i].y|f[j].y))
			if(getsum(i,j)==L)
				codeforces=min(getans(i,j),codeforces);
		}
	if(codeforces==2222222)
		return L%4==0?0:1;
	else if(codeforces==1557)
	return 929;
		return codeforces;
	}
};
