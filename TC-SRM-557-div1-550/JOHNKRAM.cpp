#include<bits/stdc++.h>
using namespace std;
const int MAXN=55,MAXM=3005;
int n,m,T,i,j,ans,h[MAXN],ne[MAXM],p[MAXM],L[MAXN],a[MAXN];
double X[MAXN],Y[MAXN],x,y,v;
bool b[MAXN],g[MAXN][MAXN];
void add(int u,int v)
{
	p[++m]=v;
	ne[m]=h[u];
	h[u]=m;
}
bool work(int now)//匈牙利算法 
{
	for(int i=h[now];i;i=ne[i])if(!b[p[i]])
	{
		b[p[i]]=1;
		if(!L[p[i]]||work(L[p[i]]))
		{
			L[p[i]]=now;
			return 1;
		}
	}
	return 0;
}
class Incubator
{
    public:
        int maxMagicalGirls(vector <string> love)
        {
            int n=love.size(),i,j,k;
            for(i=0;i<n;i++)for(j=0;j<n;j++)g[i][j]=love[i][j]=='Y';
            for(k=0;k<n;k++)for(i=0;i<n;i++)for(j=0;j<n;j++)g[i][j]=g[i][j]||g[i][k]&&g[k][j];//传递闭包 
            for(i=0;i<n;i++)for(j=0;j<n;j++)if(g[i][j])add(i,j);
            for(i=j=0;i<n;i++)//二分图最大匹配 
            {
                memset(b,0,sizeof(b));
                j+=work(i);
            }
            return n-j;
        }
};