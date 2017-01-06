#include<bits/stdc++.h>
using namespace std;
#define P 100007
#define ll long long
struct node
{
    double x,y;
    node(double _x=0,double _y=0)
    {
        x=_x;
        y=_y;
    }
    node operator-(const node& b)const
    {
        return node(x-b.x,y-b.y);
    }
    double operator*(const node& b)const//叉积 
    {
        return x*b.y-y*b.x;
    }
}a[300],b[100];
double PI=acos(-1.0);
int n,m,i,j,k,l,s[300][300],d[300],f[300][300],g[300][300],h[300][300][2];
bool c[300][300];
class FencingPenguins
{
    public:
        int countWays(int numPosts, int radius, vector <int> x, vector <int> y, string color)
        {
            n=numPosts;
            m=x.size();
            for(i=0;i<n;i++)a[i+1]=node(cos(2*PI*i/n),sin(2*PI*i/n));//坐标进行了一次放缩 
            for(i=0;i<m;i++)b[i]=node(x[i]*1.0/radius,y[i]*1.0/radius);
            for(a[n+1]=a[i=1];i<=n;i++)
            {
                for(j=0;j<m;j++)if((a[i+1]-a[i])*(b[j]-a[i])<=0)return 0;//判断是否所有点都在多边形内 
                for(j=i+1;j<=n;j++)
                {
                    c[i][j]=1;
                    for(k=0;k<m;k++)d[color[k]]=-1;
                    for(k=0;k<m;k++)
                    {
                        s[i][j]+=l=(a[i]-a[j])*(b[k]-a[j])>0;//求多边形(i,i+1,i+2,...,j)内点数 
                        if(!~d[color[k]])d[color[k]]=l;
                        c[i][j]&=d[color[k]]==l;//判断对角线<i,j>能不能连 
                    }
                }
            }
            for(i=1;i<=n;i++)f[i][i-1]=f[i][i]=g[i][i]=h[i][i][1]=1;
            for(l=1;l<n;l++)for(i=1;i+l<=n;i++)
            {
                for(j=i+l,k=i+1;k<=j;k++)if(s[i+1][k-1]==s[i][k])//连接i与k 
                {
                    h[i][j][1]=(h[i][j][1]+(ll)f[i+1][k-1]*h[k][j][1])%P;//不连接i与j 
                    g[i][j]=(g[i][j]+(ll)f[i+1][k-1]*h[k][j][s[i][k]+s[k][j]<s[i][j]])%P;//连接i与j 
                }
                h[i][j][0]=g[i][j];
                if(!c[i][j])g[i][j]=0;
                if(!s[i][j])
                {
                    g[i][j]=h[i][j][0]=0;
                    f[i][j]=1;
                    continue;
                }
                for(k=i;k<=j;k++)if(s[i][k-1]+s[k][j]==s[i][j])f[i][j]=(f[i][j]+(ll)f[i][k-1]*g[k][j])%P;//枚举最后一个环的起点 
            }
            return f[1][n];
        }
};